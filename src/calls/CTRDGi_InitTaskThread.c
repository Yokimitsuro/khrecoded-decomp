extern void OS_CreateThread(void *thread, void (*func)(void *), void *arg, void *stack, unsigned stackSize, unsigned prio);
extern void OS_WakeupThreadDirect(void *thread);
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void MIi_CpuFill24(void *p);
extern void func_02012808(void *arg);

extern void *data_0205a488;
extern char data_0205a48c;
extern char data_0205a8b0;

void CTRDGi_InitTaskThread(char *p) {
    int state = OS_DisableInterrupts();
    if (data_0205a488 == 0) {
        data_0205a488 = p;
        MIi_CpuFill24(p + 0xc4);
        MIi_CpuFill24(&data_0205a48c);
        *(int *)(p + 0xc0) = 0;
        OS_CreateThread(p, func_02012808, p, &data_0205a8b0, 0x400, 0x14);
        OS_WakeupThreadDirect(p);
    }
    OS_RestoreInterrupts(state);
}
