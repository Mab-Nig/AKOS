#ifndef AK_CRITICAL_H
#define AK_CRITICAL_H

#include "ak_cfg.h"
#include "ak_cpu.h"

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern uint32_t ak_sched_lock_nest_cnt;

#if (AK_CFG_POST_DEFERRED_EN)
#  define AK_CRITICAL_ENTER() CPU_CRITICAL_ENTER()
#  define AK_CRITICAL_EXIT()  CPU_CRITICAL_EXIT()

#  define AK_SCHED_LOCK()                                                      \
    do {                                                                       \
      CPU_CRITICAL_ENTER();                                                    \
      ++ak_sched_lock_nest_cnt;                                                \
      CPU_CRITICAL_EXIT();                                                     \
    } while (0)

#  define AK_SCHED_UNLOCK()                                                    \
    do {                                                                       \
      CPU_CRITICAL_ENTER();                                                    \
      --ak_sched_lock_nest_cnt;                                                \
      if (ak_sched_lock_nest_cnt == 0) {                                       \
        ak_sched_run();                                                        \
      }                                                                        \
      CPU_CRITICAL_EXIT();                                                     \
    } while (0)
#else /* AK_CFG_POST_DEFERRED_EN */
#  define AK_CRITICAL_ENTER() CPU_CRITICAL_ENTER()
#  define AK_CRITICAL_EXIT()  CPU_CRITICAL_EXIT()
#endif /* !AK_CFG_POST_DEFERRED_EN */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_CRITICAL_H */