#ifndef AK_PLATFORM_H
#define AK_PLATFORM_H

#include "ak_cfg.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef ENABLE
#define ENABLE          1U
#endif

#ifndef DISABLE
#define DISABLE         0U
#endif

extern uint32_t ak_sched_lock_nesting_ctr;

#if (AK_CFG_ISR_DEFERRED_EN == 1)
#define AK_CRITICAL_ENTRY()             CPU_CRITICAL_ENTRY()
#define AK_CRITICAL_EXIT()              CPU_CRITICAL_EXIT()
#define AK_CRITICAL_EXIT_NO_SCHED()     CPU_CRITICAL_EXIT_NO_SCHED()
#else
#define AK_CRITICAL_ENTRY()                     \
        do {                                    \
            CPU_CRITICAL_ENTRY();               \
            ak_sched_lock_nesting_ctr++;        \
            CPU_CRITICAL_EXIT();                \
        } while(0)

#define AK_CRITICAL_EXIT()                      \
        do {                                    \
            CPU_CRITICAL_ENTRY();               \
            ak_sched_lock_nesting_ctr--;        \
            if (ak_sched_lock_nesting_ctr == 0) \
            {                                   \
                ak_sched_switch();              \
            }                                   \
            CPU_CRITICAL_EXIT();                \
        } while(0)

#define AK_CRITICAL_EXIT_NO_SCHED()             \
        do {                                    \
            CPU_CRITICAL_ENTRY();               \
            ak_sched_lock_nesting_ctr--;        \
            CPU_CRITICAL_EXIT();                \
        } while(0)

#endif /* AK_CFG_ISR_DEFERRED_EN */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_PLATFORM_H */