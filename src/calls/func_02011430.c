extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int func_0201105c(void);
extern char *func_02011050(void);

int func_02011430(int callback) {
    int enabled = OS_DisableInterrupts();
    int err = func_0201105c();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    *(int *)(func_02011050() + 0xc8) = callback;
    OS_RestoreInterrupts(enabled);
    return 0;
}
