/* Idle thread: enable interrupts once, then halt forever. */
extern void func_0200494c(void);
extern void OS_Halt(void);

void func_02004d34(void) {
    func_0200494c();
    for (;;) {
        OS_Halt();
    }
}
