# Requirement References

- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::$$ $$
  ISR-to-task and task-to-task response time.\]\[ISR-to-task and
  task-to-task response time.\]\]

# Overview

A context switch consists of saving the context (i.e. CPU registers)
associated with one task and restore the context of a new, higher
prioritized task.

The switching algorithm is different whether the context switch is
initated by task-level code or by an ISR.

If the CPU already saves some of the context at ISR entry, the kernel
only needs to save the remaining.
