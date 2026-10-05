#include "nitro/types.h"

typedef struct WirelessHelperState {
    u16 sysState;
    u8 pad_02[6];
    u16 initialized;
    u16 errorCode;
    u8 pad_0c[0x14];
    int receiver;
    int sendBufferSize;
    u8 pad_28[8];
    int parentState;
    u8 pad_34[8];
    int recvBufferSize;
    u8 pad_40[4];
    int childBitmap;
    void (*indicateCallback)(void *arg);
} WirelessHelperState;

typedef struct ParentParam {
    void *userGameInfo;
    u16 userGameInfoLength;
} ParentParam;

extern WirelessHelperState data_ov015_0207e980;
extern ParentParam data_ov015_0207ea20;
extern u8 data_ov015_0207efa0[];
extern u8 data_ov015_0207eb60[];
extern u8 data_ov015_0207e9f4[];
extern void func_ov015_02074ce0(void *arg);
extern void MI_CpuFill8(void *dest, u8 data, u32 size);
extern BOOL func_ov015_02074d00(void);

BOOL WH_Initialize(void)
{
    if (data_ov015_0207e980.initialized) {
        return FALSE;
    }
    if (data_ov015_0207e980.indicateCallback == NULL) {
        data_ov015_0207e980.indicateCallback = func_ov015_02074ce0;
    }
    data_ov015_0207e980.recvBufferSize = 0;
    data_ov015_0207e980.sendBufferSize = 0;
    data_ov015_0207e980.childBitmap = 0;
    data_ov015_0207e980.errorCode = 0;
    data_ov015_0207e980.sysState = 1;
    data_ov015_0207e980.receiver = 0;
    data_ov015_0207ea20.userGameInfo = NULL;
    data_ov015_0207ea20.userGameInfoLength = 0;
    MI_CpuFill8(data_ov015_0207efa0, 0, 0x400);
    MI_CpuFill8(data_ov015_0207eb60, 0, 0xc0);
    MI_CpuFill8(data_ov015_0207e9f4, 0, 0x18);
    data_ov015_0207e980.parentState = 0;
    if (!func_ov015_02074d00()) {
        return FALSE;
    }
    data_ov015_0207e980.initialized = 1;
    return TRUE;
}
