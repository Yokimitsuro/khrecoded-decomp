#include "nitro/types.h"

typedef void (*WMCallbackFunc)(void *arg);

typedef struct WirelessHelper {
    u8 pad_00[0x24];
    u32 sendBufferSize;
    u8 pad_28[0x3c - 0x28];
    u32 recvBufferSize;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern u16 data_ov015_0207ec20[];
extern u16 data_ov015_0207eac0[];
extern int WM_StartMP(WMCallbackFunc callback, u16 *recvBuf, u16 recvBufSize, u16 *sendBuf, u16 sendBufSize, u16 mpFreq);
extern void WH_SetError(int code);
extern void func_ov015_02074468(void *arg);

BOOL WH_StateInStartChildMP(void)
{
    int result;

    result = WM_StartMP(func_ov015_02074468, data_ov015_0207ec20, data_ov015_0207e980.recvBufferSize, data_ov015_0207eac0, data_ov015_0207e980.sendBufferSize, 1);
    if (result != 2) {
        WH_SetError(result);
        return FALSE;
    }
    return TRUE;
}
