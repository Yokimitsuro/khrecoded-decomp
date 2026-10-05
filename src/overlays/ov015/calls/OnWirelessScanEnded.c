#include "nitro/types.h"

typedef struct WirelessCallback {
    u16 apiId;
    u16 errorCode;
} WirelessCallback;

typedef struct WirelessHelperState {
    u16 unk_00;
    u16 autoConnect;
    u8 pad_04[0x18];
    void *childKeyGenerator;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern BOOL SetChildWepKey(void);
extern BOOL StartWirelessChild(void);

void OnWirelessScanEnded(WirelessCallback *callback)
{
    if (callback->errorCode != 0) {
        WH_SetError(callback->errorCode);
        return;
    }
    SetPanelTransitionMode(1);
    if (!data_ov015_0207e980.autoConnect) {
        return;
    }
    data_ov015_0207e980.autoConnect = 0;
    if (data_ov015_0207e980.childKeyGenerator != NULL) {
        if (!SetChildWepKey()) {
            SetPanelTransitionMode(9);
        }
    } else {
        if (!StartWirelessChild()) {
            SetPanelTransitionMode(9);
        }
    }
}
