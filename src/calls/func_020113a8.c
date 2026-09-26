extern int func_0200494c(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_020597fc;

int func_020113a8(void) {
    int enabled = func_0200494c();
    char *session = *(char **)((char *)&data_020597fc + 4);
    unsigned short value;
    if (session != 0) {
        value = *(unsigned short *)(session + 0x150);
    } else {
        value = 0;
    }
    OS_RestoreInterrupts(enabled);
    return value;
}
