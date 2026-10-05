extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern int IsDeviceReady(void);
extern char *func_02011050(void);

int SetSessionCallback(int callback) {
    int enabled = OS_DisableInterrupts();
    int err = IsDeviceReady();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    *(int *)(func_02011050() + 0xc8) = callback;
    OS_RestoreInterrupts(enabled);
    return 0;
}
