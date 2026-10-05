#include "nitro/types.h"

typedef struct WirelessHelper {
    u16 scanActive;
    u8 pad_02[8];
    u16 scanCount;
    u8 pad_0c[0x50 - 0xc];
    int sysState;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern int AlarmCallback_02011848(void (*callback)(void *));
extern void WH_SetError(int code);
extern void func_ov015_02073980(void *arg);

BOOL WH_StartScanStep(void)
{
    int result;

    if ((u32)(data_ov015_0207e980.sysState - 4) <= 2) {
        return TRUE;
    }
    result = AlarmCallback_02011848(func_ov015_02073980);
    if (result == 2) {
        data_ov015_0207e980.scanCount = 0;
        data_ov015_0207e980.scanActive = 1;
        return TRUE;
    }
    WH_SetError(result);
    return FALSE;
}
