#include "nitro/types.h"

typedef u16 (*ChildWepKeyGenerator)(u16 *wepKey, void *parentInfo);

typedef struct WirelessHelperState {
    u8 pad_00[0x1c];
    ChildWepKeyGenerator childKeyGenerator;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u16 data_ov015_0207e9e0[];
extern u8 data_ov015_0207eb60[];
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern void func_ov015_02074250(void *callbackData);
extern int WM_SetWEPKey(void (*callback)(void *), u16 wepMode, const u16 *wepKey);

BOOL SetChildWepKey(void)
{
    int result;
    u16 wepMode;

    SetPanelTransitionMode(3);
    wepMode = data_ov015_0207e980.childKeyGenerator(data_ov015_0207e9e0, data_ov015_0207eb60);
    result = WM_SetWEPKey(func_ov015_02074250, wepMode, data_ov015_0207e9e0);
    if (result == 2) {
        return TRUE;
    }
    WH_SetError(result);
    SetPanelTransitionMode(9);
    return FALSE;
}
