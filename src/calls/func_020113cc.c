extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_020597fc;

unsigned short func_020113cc(void) {
    int enabled = func_0200494c();
    char *session = *(char **)((char *)&data_020597fc + 4);
    int value;
    if (session != 0) {
        value = *(int *)(session + 0x14c);
    } else {
        value = 0;
    }
    OS_RestoreInterrupts(enabled);
    return (unsigned short)value;
}
