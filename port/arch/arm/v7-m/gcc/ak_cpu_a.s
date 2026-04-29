cpu_save_curr_state:
    mrs     r0, primask
    cpsid   i
    bx lr

cpu_restore:
    msr     primask, r0
    bx      lr
