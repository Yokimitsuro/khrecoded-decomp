typedef unsigned short u16;
extern volatile u16 data_02056ec4;
extern void PXI_Init(void);
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*callback)(int, unsigned int));
extern void OSi_CommonCallback(int, unsigned int);
void OS_InitReset(void)
{
    if (data_02056ec4 != 0) return;
    data_02056ec4 = 1;
    PXI_Init();
    while (!PXI_IsCallbackReady(12, 1)) {
    }
    PXI_SetFifoRecvCallback(12, OSi_CommonCallback);
}