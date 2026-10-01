typedef struct OSThreadState {
    unsigned char padding00[0x20];
    void *currentThread;
} OSThreadState;

extern OSThreadState data_02056b50;
extern int OS_DisableInterrupts(void);
extern void OSi_ExitThread_ArgSpecified(void *thread, void *argument);

void OS_ExitThread(void)
{
    OS_DisableInterrupts();
    OSi_ExitThread_ArgSpecified(data_02056b50.currentThread, 0);
}
