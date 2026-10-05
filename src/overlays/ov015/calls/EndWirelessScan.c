#include "nitro/types.h"

typedef struct WirelessHelperState {
    u16 unk_00;
    u16 autoConnect;
    u8 pad_04[0x4c];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern void SetPanelTransitionMode(int state);

BOOL EndWirelessScan(void)
{
    if (data_ov015_0207e980.sysState == 2) {
        data_ov015_0207e980.autoConnect = 0;
        SetPanelTransitionMode(3);
        return TRUE;
    }
    return FALSE;
}
