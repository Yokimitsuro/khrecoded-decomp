/* Retries the PXI request until it is accepted. */
extern int PXI_SendWordByFifo(int a, int b, int c);

void RequestCommandProc(void) {
    int cmd = 7;
    int zero = 0;
    while (PXI_SendWordByFifo(cmd, zero, zero) < 0) {
        ;
    }
}
