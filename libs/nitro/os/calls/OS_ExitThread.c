typedef struct OSThreadState {
    unsigned char padding00[0x20];
    void *currentThread;
} OSThreadState;

extern OSThreadState OSi_ThreadSystemState;
extern int OS_DisableInterrupts(void);
extern void OSi_ExitThread_ArgSpecified(void *thread, void *argument);

void OS_ExitThread(void)
{
    OS_DisableInterrupts();
    OSi_ExitThread_ArgSpecified(OSi_ThreadSystemState.currentThread, 0);
}
