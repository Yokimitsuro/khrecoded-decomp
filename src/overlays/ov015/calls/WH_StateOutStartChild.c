#include "nitro/types.h"

typedef struct StartConnectCallback {
    u16 apiid;
    u16 errcode;
    u16 wlCmdID;
    u16 wlResult;
    u16 state;
    u16 aid;
} StartConnectCallback;

typedef struct WirelessHelperState {
    u8 pad_00[0xa];
    u16 myAid;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern BOOL WH_StateInStartChildMP(void);

void WH_StateOutStartChild(StartConnectCallback *callback)
{
    if (callback->errcode != 0) {
        WH_SetError(callback->errcode);
        if (callback->errcode == 12) {
            SetPanelTransitionMode(9);
            return;
        } else if (callback->errcode == 11) {
            SetPanelTransitionMode(9);
            return;
        } else if (callback->errcode == 1) {
            SetPanelTransitionMode(8);
            return;
        } else {
            SetPanelTransitionMode(9);
        }
        return;
    }

    if (callback->state == 8) {
        return;
    }

    if (callback->state == 7) {
        SetPanelTransitionMode(4);
        if (!WH_StateInStartChildMP()) {
            SetPanelTransitionMode(3);
            return;
        }
        data_ov015_0207e980.myAid = callback->aid;
        return;
    } else if (callback->state == 6) {
        return;
    } else if (callback->state == 9) {
        WH_SetError(20);
        SetPanelTransitionMode(9);
        return;
    } else if (callback->state == 26) {
        return;
    }

    SetPanelTransitionMode(9);
}
