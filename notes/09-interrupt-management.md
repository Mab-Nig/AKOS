# Requirement References

- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  ISR-to-task and task-to-task response time.\]\[ISR-to-task and
  task-to-task response time.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  Interrupt disable and scheduler lock time per task.\]\[Interrupt
  disable and scheduler lock time per task.\]\]

# Overview

An **interrupt** is a hardware mechanism used to inform the CPU that an
asynchronous event occurred.

When an interrupt is recognized, the CPU saves part (or all) of its
context and jumps to a special subroutine called an **Interrupt Service
Routine (ISR)**. Upon completion of the ISR, the program either returns
to the interrupted task, or the highest priority task, if the ISR made a
higher prioritized task ready-to-run.

In a real-time environment, interrupts should be disabled as little as
possible.

Interrupts can be nested.

**Interrupt disable time**: the amount of time interrupts are disabled.

**Interrupt response time**: the time between the reception of ther
interrupt and the start of its handler.

**Interrupt recovery**: the time required to return to **thread** mode
from **exception** mode.

**Task latency**: the time between the occurrence of the interrupt and
the resume of task-level code.

# Handling CPU interrupts

An **interrupt controller** captures all different interrupts.

CPUs deal with interrupts using one of the two models:

- All interrupts vector to a single interrupt handler.
- Each interrupt vectors directly to an interrupt handler.

The first thing the interrupt handler must do is saving the context of
the CPU onto the **interrupt task's stack**. The full context of the CPU
should be saved, including FPU's registers if there is one.

Increment the interrupt nesting counter on handler entry, and decrement
on exit.

# Direct and Deferred Post Methods

## Direct Post

Disabling interrupts in critical sections.

**interrupt latency** = maximum interrupt disable time.

**interrupt response** = interrupt latency

- vectoring to the interrupt handler
- ISR prologue.

**interrupt recovery** = handling of the interrupting device

- posting a signal or a message to a task
- `os_int_exit()`
- `os_int_ctx_switch()`.

**task latency** = interrupt response

- interrupt recovery
- time scheduler is locked.

The execution times of the ISR prologue, ISR epilogue, `os_int_exit()`,
and `os_int_ctw_switch()` can be measured independently and should be
fairly constant.

## Deferred Post

Locks the scheduler in critical sections.

The ISR queues the post call along with arguments in an **Interrupt
Queue**. The ISR then makes the **Interrupt Queue Handler Task**
ready-to-run. This task always has the highest priority.

Calculation of interrupt latency, interrupt response, and interrupt
recovery is the same as in direct post method.

**task latency** = interrupt response

- interrupt recovery
- re-issue the post the object or task
- context switch to task
- time scheduler is locked.

## Direct vs Deferred Post Methods

Consider using the deferred post method when:

- Multiple tasks at the same priority.
- Event flags.
- Pend on multiple objects.
- Broadcast on Post calls.

# Clock Tick (System Tick)

A hardware timer configured to generate an interrupt at a rate between
10 to 1000 Hz provides the clock tick.

The clock tick interrupt can be view as the system's heartbeat.

Many low-power applications may not implement the system tick because of
the power to maintain the **tick list**.
