typedef struct OSThread OSThread;

typedef void (*OSSwitchThreadCallback)(OSThread *from, OSThread *to);

typedef struct OSThreadInfo {
    unsigned char padding00[0x28];
    OSSwitchThreadCallback switchCallback;
} OSThreadInfo;

extern OSThreadInfo OSi_ThreadSystemState;
extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

OSSwitchThreadCallback OS_SetSwitchThreadCallback(OSSwitchThreadCallback callback)
{
    int interruptState;
    OSSwitchThreadCallback previousCallback;

    interruptState = OS_DisableInterrupts();
    previousCallback = OSi_ThreadSystemState.switchCallback;
    OSi_ThreadSystemState.switchCallback = callback;
    OS_RestoreInterrupts(interruptState);
    return previousCallback;
}