extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);
extern char *data_02057c50;

/* Length of the pending sound-command list. */
int SND_CountReservedCommand(void) {
    int enabled = func_0200494c();
    int count = 0;
    char *cmd = *(char **)&data_02057c50;
    while (cmd != 0) {
        cmd = *(char **)cmd;
        count++;
    }
    OS_RestoreInterrupts(enabled);
    return count;
}
