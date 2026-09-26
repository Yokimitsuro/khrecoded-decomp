extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);
extern void func_02002abc(void *queue);
extern void OS_WakeupThread(void *queue);
extern long long _s32_div_f(int a, int b);

/* Appends a message to the queue. Without the blocking flag a full queue fails instead of waiting. */
int OS_SendMessage(char *q, void *msg, int flags) {
    int enabled = func_0200494c();
    while (*(int *)(q + 0x14) <= *(int *)(q + 0x1c)) {
        if ((flags & 1) == 0) {
            OS_RestoreInterrupts(enabled);
            return 0;
        }
        func_02002abc(q);
    }
    (*(void ***)(q + 0x10))[(int)(_s32_div_f(
        *(int *)(q + 0x18) + *(int *)(q + 0x1c), *(int *)(q + 0x14)) >> 32)] = msg;
    *(int *)(q + 0x1c) = *(int *)(q + 0x1c) + 1;
    OS_WakeupThread(q + 8);
    OS_RestoreInterrupts(enabled);
    return 1;
}
