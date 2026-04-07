#ifndef AK_TASK_H
#define AK_TASK_H

#include "ak_list.h"
#include "ak_prio.h"

typedef struct _ak_tcb *ak_task_id_t;
struct _ak_tcb {
  ak_list_node_t sched_node;
  ak_prio_t prio;
};

#endif /* AK_TASK_H */
