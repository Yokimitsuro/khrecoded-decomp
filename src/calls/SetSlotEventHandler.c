extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MI_CpuFill8(void *dst, int value, int size);
extern void OS_GetMacAddress(void *dst);
extern int IsDeviceReady(void);
extern char *func_02011050(void);
extern unsigned short GetSessionLinkState(void);
extern int GetSessionChannel(void);

int SetSlotEventHandler(int slot, void (*callback)(void *), void *arg) {
    char event[0x44];
    char *state;
    int enabled;
    int err;
    if (callback != 0) {
        MI_CpuFill8(event, 0, 0x44);
        *(short *)event = 0x82;
        *(short *)(event + 2) = 0;
        *(short *)(event + 4) = 0x19;
        *(short *)(event + 6) = (short)slot;
        *(int *)(event + 8) = 0;
        *(int *)(event + 0xc) = 0;
        *(short *)(event + 0x10) = 0;
        *(unsigned short *)(event + 0x1a) = 0xffff;
        *(void **)(event + 0x1c) = arg;
        *(short *)(event + 0x12) = 0;
        OS_GetMacAddress(event + 0x14);
    }
    enabled = OS_DisableInterrupts();
    err = IsDeviceReady();
    if (err != 0) {
        OS_RestoreInterrupts(enabled);
        return err;
    }
    state = func_02011050() + slot * 4;
    *(void **)(state + 0xcc) = (void *)callback;
    *(void **)(state + 0x10c) = arg;
    if (callback != 0) {
        *(short *)(event + 0x22) = (short)GetSessionLinkState();
        *(short *)(event + 0x20) = (short)GetSessionChannel();
        callback(event);
    }
    OS_RestoreInterrupts(enabled);
    return 0;
}
