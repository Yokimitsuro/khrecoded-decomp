/* Idle thread: enable interrupts once, then halt forever. */
extern void OS_DisableInterrupts(void);
extern void OS_Halt(void);

void func_02004d34(void) {
    OS_DisableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
