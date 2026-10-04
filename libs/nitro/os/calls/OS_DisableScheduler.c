typedef unsigned long u32;
typedef int OSIntrMode;

typedef struct OSThreadSystemState {
    u32 reserved000;
    u32 rescheduleCount;
} OSThreadSystemState;

extern OSThreadSystemState OSi_ThreadSystemState;
extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode mode);

u32 OS_DisableScheduler(void)
{
    OSIntrMode interruptMode = OS_DisableInterrupts();
    u32 count;

    if (OSi_ThreadSystemState.rescheduleCount < (u32)(0 - 1)) {
        count = OSi_ThreadSystemState.rescheduleCount++;
    }
    (void)OS_RestoreInterrupts(interruptMode);

    return count;
}