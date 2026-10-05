extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

extern char *data_020597fc;

unsigned short GetSessionLinkState(void) {
    int enabled = OS_DisableInterrupts();
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
