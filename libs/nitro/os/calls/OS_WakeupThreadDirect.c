extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);
extern void OSi_RescheduleThread(void);

/* Marks a thread runnable and reschedules immediately, without going through the wait queue. */
void OS_WakeupThreadDirect(char *thread) {
    int enabled = func_0200494c();
    *(int *)(thread + 0x64) = 1;
    OSi_RescheduleThread();
    OS_RestoreInterrupts(enabled);
}
