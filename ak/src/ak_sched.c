#include "ak_sched.h"
#include "ak_cfg.h"
#include "ak_list.h"
#include "ak_prio.h"
#include "ak_task.h"
#include "port.h"

#include <stddef.h>
#include <stdio.h>

ak_tcb_t* g_ak_sched_run;
ak_tcb_t* g_ak_sched_high_rdy;
static uint32_t _ak_sched_lock_nest_cnt;
static ak_tcb_t* _ak_rdy_tbl[AK_CFG_PRIO_MAX + 1];
static ak_tcb_t* _ak_rdy_ends[AK_CFG_PRIO_MAX + 1];

static inline void _ak_sched_upd_high_rdy(void);
static int _ak_sched_rdy_ins(ak_tcb_t* task);
static int _ak_sched_rdy_rm(ak_tcb_t* task);

void ak_sched_reset(void) {
  g_ak_sched_run = NULL;
  g_ak_sched_high_rdy = NULL;
  ak_prio_reset();
  for (int i = 0; i <= AK_CFG_PRIO_MAX; ++i) {
    _ak_rdy_tbl[i] = NULL;
    _ak_rdy_ends[i] = NULL;
  }
}

void ak_sched_switch(void) {
  _ak_sched_upd_high_rdy();

  ak_tcb_t* tmp = g_ak_sched_run;
  g_ak_sched_run = g_ak_sched_high_rdy;
  g_ak_sched_high_rdy = tmp;

  _ak_sched_rdy_rm(g_ak_sched_run);
  _ak_sched_rdy_ins(g_ak_sched_high_rdy);
}

void ak_sched_lock(void) {
  AK_CPU_CRIT_ENTER();
  ++_ak_sched_lock_nest_cnt;
#ifdef PORT_SCHED_LOCK
  PORT_SCHED_LOCK();
#endif /* PORT_SCHED_LOCK */
  AK_CPU_CRIT_EXIT();
}

void ak_sched_unlock(void) {
  AK_CPU_CRIT_ENTER();
  --_ak_sched_lock_nest_cnt;
  if (!_ak_sched_lock_nest_cnt) {
#ifdef PORT_SCHED_LOCK
    PORT_SCHED_UNLOCK();
#endif /* PORT_SCHED_LOCK */
  }
  AK_CPU_CRIT_EXIT();
}

void _ak_sched_upd_high_rdy(void) {
  ak_prio_t max_prio = ak_prio_get_max();
  g_ak_sched_high_rdy = (max_prio >= 0 ? _ak_rdy_tbl[max_prio] : NULL);
}

int _ak_sched_rdy_ins(ak_tcb_t* task) {
#ifndef NDEBUG
  if (!task) {
    return -1;
  }
#endif /* NDEBUG */

  ak_prio_t res;

  if (ak_prio_bit_set(task->prio) < 0) {
    res = -1;

  } else {
    res = 0;

    ak_tcb_t** tbl_ent = &_ak_rdy_tbl[task->prio];
    ak_tcb_t** ends_ent = &_ak_rdy_ends[task->prio];
    if (!(*tbl_ent)) {
      *tbl_ent = *ends_ent = task;
    } else {
      *ends_ent = ak_list_ins_aft(
        &(*ends_ent)->sched_node, &task->sched_node,
        offsetof(ak_tcb_t, sched_node)
      );
    }
  }

  return res;
}

int _ak_sched_rdy_rm(ak_tcb_t* task) {
#ifndef NDEBUG
  if (!task) {
    return -1;
  }
#endif /* NDEBUG */

  ak_tcb_t** tbl_ent = &_ak_rdy_tbl[task->prio];
  ak_tcb_t** ends_ent = &_ak_rdy_ends[task->prio];

  if (!(*tbl_ent)) {
    return -1;
  }

  if (*ends_ent == task) {
    *ends_ent = task->sched_node.prev;
  }
  if (*tbl_ent == task) {
    *tbl_ent = task->sched_node.next;
  }
  ak_list_rm(&task->sched_node, offsetof(ak_tcb_t, sched_node));
  return 0;
}
