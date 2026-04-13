#include "ak_sched.h"
#include "ak_cfg.h"
#include "ak_list.h"
#include "ak_prio.h"
#include "ak_task.h"

#include <stddef.h>

ak_tcb_t* ak_sched_running;
ak_tcb_t* ak_sched_high_rdy;
static ak_tcb_t* _ak_rdy_tbl[AK_CFG_PRIO_MAX]; /* prio idx+1 at idx  */
static ak_tcb_t* _ak_rdy_ends[AK_CFG_PRIO_MAX];

static inline void _ak_sched_upd_high_rdy(void);
static ak_prio_t _ak_sched_rdy_ins(ak_tcb_t* task);
static int _ak_sched_rdy_rm(ak_tcb_t* task);

void _ak_sched_upd_high_rdy(void) {
  ak_prio_t max_prio = ak_prio_get_max();
  ak_sched_high_rdy = (max_prio ? _ak_rdy_tbl[max_prio - 1] : NULL);
}

ak_prio_t _ak_sched_rdy_ins(ak_tcb_t* task) {
  if (!task) {
    return 0;
  }

  ak_prio_t res;

  if (ak_prio_bit_set(task->prio) < 0) {
    res = 0;

  } else {
    res = task->prio;

    ak_tcb_t** tbl_ent = &_ak_rdy_tbl[task->prio - 1];
    ak_tcb_t** ends_ent = &_ak_rdy_ends[task->prio - 1];
    if (!(*tbl_ent)) {
      *tbl_ent = *ends_ent = task;
    } else {
      *ends_ent = ak_list_ins_aft(
        &(*ends_ent)->sched_node, &task->sched_node,
        offsetof(ak_tcb_t, sched_node)
      );
    }
    _ak_sched_upd_high_rdy();
  }

  return res;
}

int _ak_sched_rdy_rm(ak_tcb_t* task) {
  if (!task) {
    return -1;
  }

  ak_tcb_t** tbl_ent = &_ak_rdy_tbl[task->prio - 1];
  ak_tcb_t** ends_ent = &_ak_rdy_ends[task->prio - 1];

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
  if (ak_sched_high_rdy == task) {
    if (*tbl_ent) {
      ak_sched_high_rdy = *tbl_ent;
    } else {
      _ak_sched_upd_high_rdy();
    }
  }
  return 0;
}
