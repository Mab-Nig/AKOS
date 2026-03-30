# Requirement References

- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::- $$ $$
  Preemptive.\]\[Preemptive.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::- $$ $$
  Round-robin scheduling of tasks at equal priority.\]\[Round-robin
  scheduling of tasks at equal priority.\]\]
- \[\[<file:~/STM32Cube/Projects/self-os/docs/requirements.org>::- $$ $$
  Unlimited number of priority levels.\]\[Unlimited number of priority
  levels.\]\]

# Priority Levels

The kernel allows upto **`OS_CFG_PRIO_MAX`** different priority levels,
ranges from **0** to **`OS_CFG_PRIO_MAX-1`**. A higher priority number
corresponds to a higher priority level.

The idle task is assigned with the lowest priority level.

Ready tasks' priorities are stored in a bitmap table. The highest
priority level/number can be retrieved by using a **Count Leading Zeros
(CLZ)** instruction (`__builtin_clz()` on GCC).

To determine the highest priority level that contains ready-to-run
tasks, the bitmap table is scanned in reverse until a set bit is
encountered.

## API

``` c
typedef uint8_t os_prio_t;

os_prio_t os_prio_get_highest(void);
void os_prio_insert(os_prio_t prio, os_task_id_t tid);
void os_prio_remove(os_prio_t prio);
```

# The Ready Table

Tasks that are ready to run are placed in the Ready Table. The ready
table is an array containing `OS_CFG_PRIO_MAX` entries, with each entry
is a pointer to a list of tasks whose priority is equal to the entry's
index.
