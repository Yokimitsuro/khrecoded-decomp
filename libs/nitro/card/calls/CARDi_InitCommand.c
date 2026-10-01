typedef unsigned char u8;
typedef unsigned long u32;

typedef struct CARDiCommon {
    void *command;
} CARDiCommon;

extern CARDiCommon cardi_common;
extern u8 cardi_arg[0x60];
extern void MIi_CpuClearFast(u32 value, void *destination, u32 size);
extern void DC_FlushRange(const void *address, u32 size);
extern void PXI_SetFifoRecvCallback(int tag, void (*callback)(int tag, u32 data, int error));
extern void CARDi_OnFifoRecv(int tag, u32 data, int error);

void CARDi_InitCommand(void)
{
    CARDiCommon *common = &cardi_common;

    common->command = cardi_arg;
    MIi_CpuClearFast(0, cardi_arg, sizeof(cardi_arg));
    DC_FlushRange(cardi_arg, sizeof(cardi_arg));
    PXI_SetFifoRecvCallback(11, CARDi_OnFifoRecv);
}