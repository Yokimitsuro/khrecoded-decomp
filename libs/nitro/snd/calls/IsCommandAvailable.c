extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern int CommandPort_IsEnabled(void);

int IsCommandAvailable(void)
{
    volatile unsigned int *commandPort = (volatile unsigned int *)0x04fff200;
    int enabled;
    unsigned int busy;

    if (CommandPort_IsEnabled() == 0) {
        return 1;
    }
    enabled = OS_DisableInterrupts();
    *commandPort = 0x10;
    busy = *commandPort;
    OS_RestoreInterrupts(enabled);
    return busy != 0;
}
