#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x50];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207f3a0[];
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern int func_02012284(void *keySetBuffer, u16 port);

BOOL StartWirelessKeySharing(void)
{
    int result;

    if (data_ov015_0207e980.sysState == 6) {
        return TRUE;
    }
    if (data_ov015_0207e980.sysState != 4) {
        return FALSE;
    }
    SetPanelTransitionMode(6);
    result = func_02012284(data_ov015_0207f3a0, 13);
    if (result != 0) {
        WH_SetError(result);
        return FALSE;
    }
    return TRUE;
}
