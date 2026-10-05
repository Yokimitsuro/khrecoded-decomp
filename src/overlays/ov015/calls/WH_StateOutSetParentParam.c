#include "nitro/types.h"

typedef struct WMCallback {
    u16 apiid;
    u16 errcode;
} WMCallback;

typedef struct WirelessHelper {
    u8 pad_00[0x34];
    void *parentKeyGenerator;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void WH_SetError(int code);
extern void SetPanelTransitionMode(u32 mode);
extern BOOL func_ov015_02073894(void);
extern BOOL func_ov015_02073930(void);

void WH_StateOutSetParentParam(WMCallback *cb)
{
    if (cb->errcode != 0) {
        WH_SetError(cb->errcode);
        SetPanelTransitionMode(9);
        return;
    }
    if (data_ov015_0207e980.parentKeyGenerator != NULL) {
        if (!func_ov015_02073894()) {
            SetPanelTransitionMode(9);
        }
    } else {
        if (!func_ov015_02073930()) {
            SetPanelTransitionMode(9);
        }
    }
}
