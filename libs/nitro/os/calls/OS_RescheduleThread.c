typedef int OSIntrMode;

extern OSIntrMode func_0200494c(void);
extern void OS_RestoreInterrupts(OSIntrMode state);
extern void OSi_RescheduleThread(void);

/* Public entry point: hand the CPU to whichever thread should have it, with the
   scheduler's own work done under a critical section. */
void OS_RescheduleThread(void)
{
    OSIntrMode nLast = func_0200494c();

    OSi_RescheduleThread();
    OS_RestoreInterrupts(nLast);
}
