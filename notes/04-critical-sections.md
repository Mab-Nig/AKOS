# Requirement References

- \[\[<file:requirements.org>::- $$ $$ Low interrupt disable
  time.\]\[Low interrupt disable time.\]\]
- \[\[<file:requirements.org>::+ $$ $$ Timestamps.\]\[Timestamps.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  Interrupt disable and scheduler lock time per task.\]\[Interrupt
  disable and scheduler lock time per task.\]\]

# Content

If a critical section is accessible by **an ISR** and **a task**, then
**disable interrupts**. Else if the section is only accessible by tasks,
then **disable scheduling**.

Critical sections are protected by:

- **Disabling interrupts** if `OS_CFG_ISR_POST_DEFERRED_EN` is set to 0.
- **Locking the scheduler** if `OS_CFG_ISR_POST_DEFERED_EN` is set to 1.

Macros used only by the kernel:

- `OS_CRITICAL_ENTER()`.
- `OS_CRITICAL_EXIT()`.

`- OS_CRITICAL_EXIT_NO_SCHED()`.

Enable measuring interrupt disable time: `CPU_CFG_DIS_MEAS_EN`. Enable
measuring scheduling lock time: `OS_CFG_LOCK_TIME_MEAS_EN`.
