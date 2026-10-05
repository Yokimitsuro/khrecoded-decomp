extern void PXI_Init(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern void CTRDG_Enable(int enable);
extern void CTRDGi_InitCommon(void);
extern void func_020125dc(void);
extern void CTRDGi_InitTaskThread(void *p);
extern void CTRDGi_InitCallback(int fifoNo, unsigned int data);
extern void CTRDGi_PulledOutCallback(int fifoNo, unsigned int data);
extern void func_0201278c(int fifoNo, unsigned int data);

extern struct {
    char _0[8];
    int initialized;
    int field_c;
    char _10[8];
    int field_18;
} data_0205a2a8;

extern char data_0205a3a0;

void CTRDG_Init(void)
{
    if (data_0205a2a8.initialized != 0)
        return;

    data_0205a2a8.initialized = 1;
    CTRDGi_InitCommon();
    data_0205a2a8.field_c = 0;
    PXI_Init();
    while (!PXI_IsCallbackReady(13, 1)) {
    }
    PXI_SetFifoRecvCallback(13, CTRDGi_InitCallback);
    func_020125dc();
    PXI_SetFifoRecvCallback(13, 0);
    PXI_SetFifoRecvCallback(13, CTRDGi_PulledOutCallback);
    data_0205a2a8.field_18 = 0;
    CTRDGi_InitTaskThread(&data_0205a3a0);
    PXI_SetFifoRecvCallback(17, func_0201278c);
    CTRDG_Enable(0);
}
