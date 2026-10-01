extern int CARDi_ReadRom(int dma, int src, int dst, int len, int callback, int callbackArg, int isAsync);
extern int FSi_OnRomReadDone(void);
extern int *data_02057b1c[];
int FSi_ReadRomCallback(int archive, int dst, int src, int len)
{
    CARDi_ReadRom((int)data_02057b1c[0], src, dst, len, (int)FSi_OnRomReadDone, archive, 1);
    return 0x100;
}