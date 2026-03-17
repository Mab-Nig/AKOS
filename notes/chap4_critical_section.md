# Summary: Critical Sections in uC/OS-III


## 1. Concept

A critical section is a block of code or shared data structure that must be executed indivisibly, without being preempted by an Interrupt Service Routine (ISR) or another task.

## 2. Two Protection Mechanisms

Depending on the `OS_CFG_ISR_POST_DEFERRED_EN` configuration in `os_cfg.h`, uC/OS-III automatically applies one of two methods to protect internal critical sections.

**Disabling Interrupts (Direct Post Method)**

- Configuration: `OS_CFG_ISR_POST_DEFERRED_EN = 0`
- Mechanism: Completely disables CPU hardware interrupts before entering the critical section and re-enables them upon exit.
- Pros: Shorter ISR-to-task response time.
- Cons: Increases interrupt latency. The CPU might miss important interrupts if the critical section is long.

**Locking the Scheduler (Deferred Post Method)**

- Configuration: `OS_CFG_ISR_POST_DEFERRED_EN = 1`
- Mechanism: Does not disable hardware interrupts. Instead, it increments `OSSchedLockNestingCtr` to lock the scheduler (preventing context switches). "Post" calls from an ISR are pushed to an Interrupt Queue and handled later by a dedicated task `OS_IntQTask()`.
- Pros: Keeps interrupt latency extremely low since interrupts are almost never disabled.
- Cons: Tacks on extra processing time for the queue, leading to a longer ISR-to-task response time.

## 3. Internal Macros

uC/OS-III uses three main macros to handle critical sections.

- `OS_CRITICAL_ENTER()`: Enter the critical section.
- `OS_CRITICAL_EXIT()`: Exit the critical section (calls the scheduler if needed).
- `OS_CRITICAL_EXIT_NO_SCHED()`: Exit the critical section (without calling the scheduler).

These macros are strictly for OS internal use. Application code must never call these macros to protect user resources; use Semaphores or Mutexes instead.

## 4. Measurement and Debugging

The OS provides features to measure system latency in real-time.

- Measure maximum interrupt disable time: Enable `CPU_CFG_INT_DIS_MEAS_EN`.
- Measure maximum scheduler lock time: Enable `OS_CFG_SCHED_LOCK_TIME_MEAS_EN`.