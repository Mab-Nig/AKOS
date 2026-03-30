# Overview

A task is placed in a **Wait List** when it is waiting on a semaphore to
be signalled, a mutual exclusion to be released, an event flag group to
be posted, or a message queue to be posted.

Each kernel object has its own wait list. A task can only wait for 1
object at a time.
