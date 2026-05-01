#ifndef AK_SCHED_H
#define AK_SCHED_H

#include "ak_cpu.h"
#include "ak_task.h"

typedef enum {RUN, RDY, WAIT, BLK} ak_state_t;

extern ak_tcb_t *g_ak_sched_run;
extern ak_tcb_t *g_ak_sched_high_rdy;
extern uint32_t g_ak_sched_lock_nest_cnt;

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void ak_sched_reset(void);
void ak_sched_switch(void);
// void ak_sched_task_switch_state(ak_tcb_t *task, ak_state_t new_state);

static inline void ak_sched_lock(void) {
  AK_CPU_CRIT_ENTER();
  ++g_ak_sched_lock_nest_cnt;
  AK_CPU_CRIT_EXIT();
}

static inline void ak_sched_unlock(void) {
  AK_CPU_CRIT_ENTER();
  --g_ak_sched_lock_nest_cnt;
  if (!g_ak_sched_lock_nest_cnt) {
    ak_sched_switch();
  }
  AK_CPU_CRIT_EXIT();
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_SCHED_H */
