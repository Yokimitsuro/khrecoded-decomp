/* Idle thread: enable interrupts once, then halt forever. */
extern void OS_EnableInterrupts(void);
extern void OS_Halt(void);

void func_02002d74(void) {
    OS_EnableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
