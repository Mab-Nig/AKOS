# Requirements Reference

- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  Execution time of each task.\]\[Execution time of each task.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  Stack usage of each task.\]\[Stack usage of each task.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  CPU usage.\]\[CPU usage.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::+ $$ $$
  Tick handling at task level (SysTick handler hook).\]\[Tick handling
  at task level (SysTick handler hook).\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::+ $$ $$
  User definable hooks.\]\[User definable hooks.\]\]

# Overview

A task is a simple program that thinks it has the CPU all to itself. The
number of tasks running in parallel is equal to the number of CPUs on a
system. That is 1 task at a time for a single-CPU computer.

RTOS allows the application to have any number of tasks. Multitasking is
the process of **scheduling** and **switching** the CPU between several
tasks. It provides the illusion of having multiple CPUs.

Multitasking helps create modular applications.

There are two type of tasks: **run-to-completion (RTC)** and **infinite
loop**. An RTC task must delete itself by calling **`os_task_del()`**.

A task can create another task (via **`os_task_new()`**), suspend and
resume other tasks (via **`os_task_suspend()`** and
**`os_task_resume()`**).

It is possible to call the same function from different tasks as long as
the function is **reentrant**.

When a task waits for an event, it does **NOT** consume CPU time.

# Determining the Size of a Task

When sizing the stack, one must account for:

- The nesting of all functions called by the task.
- The number of local variables to be allocated by all functions called
  by the task.
- The stack requirements for all nested ISRs.
- All **CPU registers** and possibly **FPU registers**.

The summed number should be multiplied by some **safety factor**,
possibly 1.5 or 2.0

Compilers/Linkers provide function stack usages in a **link map**.

**Avoid** writing recursive code.

**Always** monitor stack usage at run-time while developing and testing
the product. Stack overflows occur often and can lead to strange
behaviors.

# Detecting Task Stack Overflows

**1. Using MMU or MPU**

**2. Using CPU with Stack Overflow Detection** Some processors have
simple stack pointer overflow detection registers. When the SP goes
below the value set in this register, an exception is generated.

**3. Software-Based Stack Overflow Detection** If the processor does not
have overflow detection registers, it is possible to simulate this
feature by adding code in the **task switch hook**.

**4. Counting the Amount of Free Stack Space** First, the task stack
needs to be cleared. Next, a low priority task **walks the stack** of
each task. Then, a more reasonable stack size of tasks can be set.

# Task Management Internals

## Task States

**Dormant:** The task resides in memory but bas not been made to the OS.

**Ready:** The task is ready to run. The kernel keeps track of all ready
tasks in a **ready list**.

**Running:** The most important ready-to-run task. The task selected to
run on the CPU is **switched** in by the kernel when:

- The OS starts.
- Exit from interrupts.
- Task switching.

**Pending/Waiting:** Tasks waiting for an event to occur. These tasks
are placed in a **pending/waiting list**. When waiting for the event,
the task does **NOT** consume CPU. When the event occurs, the task is
**placed back into the ready list**.

# Internal Tasks

The **Idle Task** can call a user-defined hook **`os_idle_hook()`**.

The **Tick Task** can call a user-defined hook **`os_tick_hook()`**.
Ticks are managed with a **chaining hash map** to quickly identify the
next tick to signal an event.

The **Statistic Task**.

The **Timer Task** can call user-defined hooks when a timer counter
reaches zero.

# API

## Definitions

`OS_CFG_TASK_NEW_HOOK_EN`

`OS_CFG_TASK_DEL_HOOK_EN`

`OS_CFG_TASK_SUSPEND_HOOK_EN`

`OS_CFG_TASK_RESUME_HOOK_EN`

`OS_CFG_TASK_SWITCH_HOOK_EN`

## Task Creation

``` c
os_task_id_t os_task_new(const os_task_params_t *params);
```

Fields of `os_task_params_t`:

| **Type**       | **Name**     | **Description**                          |
|----------------|--------------|------------------------------------------|
| `const char *` | `name`       | Task name.                               |
|                |              | Default: NULL - no name is specified.    |
| `uint32_t`     | `attr_bits`  | Attribute bits:                          |
|                |              | \- OS<sub>TASKDETACHED</sub>             |
|                |              | \- OS<sub>TASKJOINABLE</sub>             |
|                |              | \- OS<sub>TASKUNPRIV</sub>               |
|                |              | \- OS<sub>TASKPRIV</sub>                 |
|                |              | \- OS<sub>THREADZONE</sub>(m)            |
|                |              | \- OS<sub>SAFETYCLASS</sub>(n)           |
|                |              | Default: 0 - no options set.             |
| `void *`       | `tcb_ptr`    | Pointer to allocated TCB.                |
|                |              | Default: NULL - automatic allocation.    |
| `size_t`       | `tcb_sz`     | Size of TCB associated with `tcb_ptr`.   |
|                |              | Needed for deallocation.                 |
|                |              | Default: 0.                              |
| `void *`       | `stk_ptr`    | Pointer to allocated task stack.         |
|                |              | Default: NULL - automatic allocation.    |
| `size_t`       | `stk_sz`     | Size of stack.                           |
|                |              | Default: 0 - use default stack size.     |
| `os_prio_t`    | `prio`       | Task priority.                           |
|                |              | Default: 0 - normal.                     |
| `tz_mod_id_t`  | `tz_mod`     | TruztZone module identifier.             |
|                |              | Default: 0 - no context specified.       |
| `uint32_t`     | `affin_mask` | Processor affinity for binding a task to |
|                |              | a CPU in a SMP system.                   |
|                |              | Default: 0 - RTOS specific               |

### Action Sequence

1.  The kernel initializes the task's stack, with the Task Control Block
    (TCB) at the start of the stack frame if `params->tcb_ptr` is not
    specified. The TCB contains CPU registers needed during context
    switches.
2.  The new value of the Stack Pointer (SP) is saved in the TCB. This is
    also called **top-of-stack**.
3.  The remaining fields of the TCB are initialized.
4.  A call is made to a user-defined hook (callback) -
    **`os_task_new_hook()`** - to extend the functionality of
    **`os_task_new()`**.
