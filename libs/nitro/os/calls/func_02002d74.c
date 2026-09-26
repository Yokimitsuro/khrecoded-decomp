/* Idle thread: enable interrupts once, then halt forever. */
extern void func_02004938(void);
extern void OS_Halt(void);

void func_02002d74(void) {
    func_02004938();
    for (;;) {
        OS_Halt();
    }
}
