# Getting started


## Single Task application

We have a file app.c, there are 2 parts: outside and inside main function.

**outside main func**

1. As with any C programs, you need to include the necessary headeers

- app_cfg.h configures the application. For example, app_cfg.h contains #define constants to establish task priority, stack sizes, ...

- bsp.h is the header file for the Board Support Package (BSP), which defines #defines and function prototypes, such as BSP_Init(), BSP_LED_On()OS_TS_GET() and more.

- os.h is the main header file for μC/OS-III.
```c
/*
***********************************************************************************************
*
INCLUDE FILES
***********************************************************************************************
*/

#include <app_cfg.h>
#include <bsp.h>
#include <os.h>
```

2. Task control block and CPU stack

```c
/*
***********************************************************************************************
*
LOCAL GLOBAL VARIABLES
***********************************************************************************************
*/
static OS_TCB AppTaskStartTCB;

static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
```

3. Function prototype of the task that we will create.

```c
/*
***********************************************************************************************
*
FUNCTION PROTOTYPES
***********************************************************************************************
*/
static void AppTaskStart (void *p_arg);
```

**inside main func**

1. Create a error check variable

```c
OS_ERR err;
```

2. Start the main function by calling BSP function that disables all interrupt (to be more explicit) then init OS (internal var, data structure, ...). Most of OS func return an error code via a pointer to an OS_ERR variable.

```c
BSP_IntDisAll();
OSInit(&err);
if (err != OS_ERR_NONE) {
/* Something didn’t get initialized correctly ...
*/
/* ... check os.h for the meaning of the error code, see OS_ERR_xxxx */
}
```

3. Create a task (OSTaskCreate()) by passing 13 argument which are:
- OS_TCB
- Task name
- Address of Task code
- Actual argument that the task receives
- Prio
- Base addr of stack
- Limit of task's stack
- Size of stack size in number of CPU_STK
- ...

4. Call OSStart()

## Multi tasks application with kernel objects

This section show a more complicated example and contains 3 tassks: a mutual exclusion, semaphore, and message queue.

**before main**

1. Include header files
```c
/*
***********************************************************************************************
*
INCLUDE FILES
***********************************************************************************************
*/
#include <app_cfg.h>
#include <bsp.h>
#include <os.h>
```

2. Init TCB, Mutex, Queue, Stack for each Task

```c
/*
***********************************************************************************************
*
LOCAL GLOBAL VARIABLES
***********************************************************************************************
*/
static OS_TCB AppTaskStartTCB;
static OS_TCB AppTask1_TCB;
static OS_TCB AppTask2_TCB;
static OS_MUTEX AppMutex;
static OS_Q AppQ;
static CPU_STK AppTaskStartStk[APP_TASK_START_STK_SIZE];
static CPU_STK AppTask1_Stk[128];
static CPU_STK AppTask2_Stk[128];
```
3. Prototype of tasks are declared
```c
/*
***********************************************************************************************
*
FUNCTION PROTOTYPES
***********************************************************************************************
*/
static void AppTaskStart (void *p_arg);
static void AppTask1 (void *p_arg);
static void AppTask2 (void *p_arg);
```

**inside main**

- The same as single task from step 1
- Create mutex by calling OSMutexCreate()
- Queue create
- First task create
- Os start

**inside AppTaskStart**

1. Init
```c

BSP_Init();
CPU_Init();
BSP_Cfg_Tick();
```

2. Create all task needed
```c
OSTaskCreate(){} // task 1
OSTaskCreate(){} // task 2
```

If any task has the higher prio than the AppTaskStart, then it will immediately switch to its task




