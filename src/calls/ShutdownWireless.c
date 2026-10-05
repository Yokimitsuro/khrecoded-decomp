extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int IsDeviceReady(void);
extern int WMi_CheckStateEx(int a, int b);
extern void func_0201138c(void);
extern void PXI_SetFifoRecvCallback(int tag, void *callback);
extern char data_020597fc;

int ShutdownWireless(void) {
    int enabled = OS_DisableInterrupts();
    int err;
    if (IsDeviceReady() != 0) {
        OS_RestoreInterrupts(enabled);
        return 3;
    }
    err = WMi_CheckStateEx(1, 0);
    if (err != 0) {
        return err;
    }
    func_0201138c();
    PXI_SetFifoRecvCallback(0xa, 0);
    *(int *)((char *)&data_020597fc + 4) = 0;
    *(short *)&data_020597fc = 0;
    OS_RestoreInterrupts(enabled);
    return 0;
}
