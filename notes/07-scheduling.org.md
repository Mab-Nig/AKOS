# Requirement References

- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::- $$ $$
  Preemptive.\]\[Preemptive.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::- $$ $$
  Round-robin scheduling of tasks at equal priority.\]\[Round-robin
  scheduling of tasks at equal priority.\]\]

# Preemptive Scheduling

The kernel handles event posting from interrupts using two different
methods: **direct** and **deferred** posting.

- Direct: ISR is processed right away.
- Deferred: Processing is redirected to a handler task, whose priority
  is just lower than the highest.

# Scheduling Points

- A task signals or sends a message to another task.
- A task delays, either on a timer or an event.
- A task aborts a pend.
- A task is created.
- A task is deleted.
- A kernel object is deleted.
- A task changes the priority of itself or another task.
- A task suspends itself.
- A task resumes another suspended task.
- At the end of all nested ISRs.
- The scheduler is unlocked.
- A task yields.

# `os_int_exit()`

There a nesting counter. The scheduler is called when this counter
reaches 0.

# Round-Robin

The time quanta counter inside the TCB of each task is decremented after
every tick. Once a counter reaches 0, the kernel checks if there are
other ready-to-run tasks at the current or higher priority.

Round-robin scheduling only applies when there are multiple tasks at the
same priority and the task doesn't complete its work within its time
quanta.
