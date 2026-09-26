extern void func_020028ac(void *thread, void (*func)(void *), void *arg, void *stack, unsigned stackSize, unsigned prio);
extern void OS_WakeupThreadDirect(void *thread);
extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);
extern void func_020127fc(void *p);
extern void func_02012808(void *arg);

extern void *data_0205a488;
extern char data_0205a48c;
extern char data_0205a8b0;

void func_02012798(char *p) {
    int state = func_0200494c();
    if (data_0205a488 == 0) {
        data_0205a488 = p;
        func_020127fc(p + 0xc4);
        func_020127fc(&data_0205a48c);
        *(int *)(p + 0xc0) = 0;
        func_020028ac(p, func_02012808, p, &data_0205a8b0, 0x400, 0x14);
        OS_WakeupThreadDirect(p);
    }
    OS_RestoreInterrupts(state);
}
