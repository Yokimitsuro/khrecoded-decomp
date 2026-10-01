extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);
extern void *data_02057b8c[];

void PXI_SetFifoRecvCallback(int fifoTag, void *callback)
{
    int enabled = OS_DisableInterrupts();
    int *systemWork = (int *)0x02fffc00;

    data_02057b8c[fifoTag] = callback;
    if (callback != 0) {
        systemWork[0xe2] |= 1 << fifoTag;
    } else {
        systemWork[0xe2] &= ~(1 << fifoTag);
    }
    OS_RestoreInterrupts(enabled);
}
