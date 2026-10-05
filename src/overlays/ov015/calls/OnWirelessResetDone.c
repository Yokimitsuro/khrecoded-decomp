#include "nitro/types.h"

typedef struct WirelessCallback {
    u16 apiId;
    u16 errorCode;
} WirelessCallback;

typedef struct WirelessHelperState {
    u8 pad_00[0x18];
    void (*onReset)(WirelessCallback *callback);
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);

void OnWirelessResetDone(WirelessCallback *callback)
{
    if (callback->errorCode != 0) {
        SetPanelTransitionMode(9);
        WH_SetError(callback->errorCode);
        return;
    }
    if (data_ov015_0207e980.onReset != NULL) {
        data_ov015_0207e980.onReset(callback);
    }
    SetPanelTransitionMode(1);
}
