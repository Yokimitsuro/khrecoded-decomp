extern void OS_DisableInterrupts(void);
extern void OS_Halt(void);

void OSi_TerminateCore(void)
{
    OS_DisableInterrupts();
    for (;;) {
        OS_Halt();
    }
}
