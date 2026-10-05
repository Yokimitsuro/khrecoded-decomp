extern int data_02060534;
extern void TP_RequestAutoSamplingStartAsync(int unknownMode0, int unknownMode1, void *stateBlock, int unknownMode2);
extern void TP_WaitBusy(int unknownMode);
extern int TP_CheckError(int unknownMode);

int func_0202b5e8(void) {
    TP_RequestAutoSamplingStartAsync(0, 4, &data_02060534, 5);
    TP_WaitBusy(2);
    return TP_CheckError(2) == 0;
}
