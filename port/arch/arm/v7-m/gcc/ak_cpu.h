#ifndef AK_CPU_H
#define AK_CPU_H

#ifndef __cplusplus
extern "C" {
#endif

#define CPU_CRITICAL_ALLOC() uint32_t cpu_state = 0
#define CPU_CRITICAL_ENTER()                                                   \
  do {                                                                         \
    cpu_state = cpu_save_curr_state();                                         \
  } while (0)
#define CPU_CRITICAL_EXIT()                                                    \
  do {                                                                         \
    cpu_restore(cpu_state);                                                    \
  } while (0)

#ifndef __cplusplus
}
#endif /* __cplusplus */

#endif /* AK_CPU_H */