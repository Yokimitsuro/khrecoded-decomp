#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x1c];
    void *childKeyGenerator;
    u8 pad_20[0x30];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207eb60[];
extern u8 data_ov015_0207e9f4[];
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern void WH_StateOutStartChild(void *callbackData);
extern int WM_StartConnectEx(void (*callback)(void *), const void *parentInfo, const u8 *ssid, BOOL powerSave, const u16 authMode);

BOOL StartWirelessChild(void)
{
    int result;

    if (data_ov015_0207e980.sysState == 4 || (u32)data_ov015_0207e980.sysState == 6 || data_ov015_0207e980.sysState == 5) {
        return TRUE;
    }
    SetPanelTransitionMode(3);
    result = WM_StartConnectEx(WH_StateOutStartChild, data_ov015_0207eb60, data_ov015_0207e9f4, TRUE,
                                        (u16)(data_ov015_0207e980.childKeyGenerator != NULL ? 1 : 0));
    if (result != 2) {
        WH_SetError(result);
        return FALSE;
    }
    return TRUE;
}
