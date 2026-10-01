typedef unsigned long u32;
typedef int BOOL;
typedef int OSIntrMode;

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void CARDi_PulledOutCallback(int tag, u32 data, BOOL error);

void CARDi_CheckPulledOutCore(u32 id)
{
    volatile u32 bootCardId = *(volatile u32 *)0x02fffc00;

    if (id != bootCardId) {
        OSIntrMode interruptState = OS_DisableInterrupts();

        CARDi_PulledOutCallback(14, 0x11, 0);
        (void)OS_RestoreInterrupts(interruptState);
    }
}