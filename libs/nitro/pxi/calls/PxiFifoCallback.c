/* Runs the sound alarm handler with interrupts disabled. */
extern int func_0200494c(void);
extern void SNDi_CallAlarmHandler(int data);
extern void OS_RestoreInterrupts(int state);

void PxiFifoCallback(int unused, int data) {
    int state = func_0200494c();
    SNDi_CallAlarmHandler(data);
    OS_RestoreInterrupts(state);
}
