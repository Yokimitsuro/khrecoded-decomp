extern void PXI_Init(void);
extern void PXI_SetFifoRecvCallback(int fifoNo, void (*cb)(int, unsigned int));
extern int PXI_IsCallbackReady(int fifoNo, int kind);
extern void TPi_TpCallback(int fifoNo, unsigned int data);

typedef struct {
    unsigned short initialized;
    char _2[0x2];
    int field_4;
    char _8[0x8];
    unsigned short field_10;
    char _12[0x2];
    int field_14;
    char _18[0x1c];
    unsigned short field_34;
    unsigned short field_36;
    unsigned short field_38;
    unsigned short field_3a;
} Data_02046390;

extern Data_02046390 data_02059784;

void TP_Init(void)
{
    if (data_02059784.initialized != 0)
        return;

    data_02059784.initialized = 1;
    PXI_Init();
    data_02059784.field_10 = 0;
    data_02059784.field_4 = 0;
    data_02059784.field_14 = 0;
    data_02059784.field_36 = 0;
    data_02059784.field_34 = 0;
    data_02059784.field_3a = 0;
    data_02059784.field_38 = 0;
    while (!PXI_IsCallbackReady(6, 1)) {
    }
    PXI_SetFifoRecvCallback(6, TPi_TpCallback);
}
