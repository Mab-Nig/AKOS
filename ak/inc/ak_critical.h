#ifndef AK_CRITICAL_H
#define AK_CRITICALCRITICAL_H

#include "stdint.h"
#include "ak_cfg.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

extern uint32_t ak_sched_lock_nest_cnt;

#if (AK_CFG_POST_DEFERRED_EN)
#define AK_CRITICAL_ENTER()                     \
        do {                                    \
            OS_CRITICAL_ENTER();                \
            extern ak_sched_lock_nest_cnt++;   \
            OS_CRITICAL_EXIT();                 \
        } while(0)

#define AK_CRITICAL_EXIT()                      \
        do {                                    \
            OS_CRITICAL_ENTER();                \
            ak_sched_lock_nest_cnt--;           \
            if (ak_sched_lock_nest_cnt == 0) {  \
                ak_sched_run();                 \
            }                                   \
            OS_CRITICAL_EXIT();                 \
        }   while(0)
#endif /* AK_CFG_POST_DEFERRED_EN == ENABLE */

#if (!AK_CFG_POST_DEFERRED_EN)
#define AK_CRITICAL_ENTER()         OS_CRITICAL_ENTER()
#define AK_CRITICAL_EXIT()          OS_CRITICAL_EXIT()
#endif /* AK_CFG_POST_DEFERRED_EN == DISABLE */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_CRITICAL_H */