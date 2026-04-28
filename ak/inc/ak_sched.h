#ifndef AK_SCHED_H
#define AK_SCHED_H

#include "ak_task.h"

typedef enum {RUN, RDY, WAIT, BLK} ak_state_t;

extern ak_tcb_t *ak_sched_run;
extern ak_tcb_t *ak_sched_high_rdy;

void ak_sched_reset(void);
void ak_sched_turnover(void);
// void ak_sched_task_switch_state(ak_tcb_t *task, ak_state_t new_state);

#endif /* AK_SCHED_H */
