extern int GX_SetBankForLCDC();
extern int MIi_CpuClearFast();
extern int GX_DisableBankForLCDC();

void ClearVideoMemory(void) {
    GX_SetBankForLCDC(0x1ff);
    MIi_CpuClearFast(0, (void *)0x06800000, 0xa4000);
    GX_DisableBankForLCDC();
    MIi_CpuClearFast(0xc0, (void *)0x07000000, 0x400);
    MIi_CpuClearFast(0xc0, (void *)0x07000400, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000000, 0x400);
    MIi_CpuClearFast(0, (void *)0x05000400, 0x400);
}
