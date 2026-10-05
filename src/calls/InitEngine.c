extern void PXI_Init_020034d8(void);
extern void BootInitHookNoOp(void);
extern void FS_Init(int priority);
extern void GX_Init(void);
extern void OS_InitTick(void);
extern void RTC_Init(void);
extern void CARD_Init(void);
extern void CARD_SetCacheFlushThreshold(int a, int b);
extern void GX_DispOff(void);
extern void SetBrightnessAndSyncMain(int value);
extern void SetSecondaryBrightness(int value);
extern void *NNS_GfdInitVramTransferManager(int a, int b);
extern void func_020010e0(void);
extern unsigned int OS_EnableIrqMask(unsigned int mask);
extern void InitEngineHeaps(int oldIme);
extern void ClearVideoMemory(void);
extern void SetupDisplayRegs(void);
extern void InitTouchPanel(void);
extern void InitRandomFromEntropy(void);

extern int GXi_DmaId;
extern int data_02060088;

void InitEngine(void)
{
    volatile unsigned short *keypadReg = (volatile unsigned short *)0x04000304;
    volatile unsigned short *ime = (volatile unsigned short *)0x04000208;
    unsigned short oldIme;

    PXI_Init_020034d8();
    BootInitHookNoOp();
    FS_Init(3);
    *keypadReg = (*keypadReg & ~0x20e) | 0x20e;
    GXi_DmaId = 1;
    GX_Init();
    OS_InitTick();
    RTC_Init();
    CARD_Init();
    CARD_SetCacheFlushThreshold(0x500, 0x2400);
    GX_DispOff();
    *(volatile unsigned int *)0x04001000 &= 0xfffeffff;
    SetBrightnessAndSyncMain(0x10);
    SetSecondaryBrightness(0x10);
    NNS_GfdInitVramTransferManager((int)&data_02060088, 0x30);
    func_020010e0();
    OS_EnableIrqMask(0x40000);
    oldIme = *ime;
    *ime = 1;
    InitEngineHeaps(oldIme);
    ClearVideoMemory();
    SetupDisplayRegs();
    InitTouchPanel();
    InitRandomFromEntropy();
}
