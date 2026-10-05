#include "nitro/types.h"

extern u32 GetPanelTransitionMode(void);
extern void BeginWirelessChannelMeasurement(void);
extern u16 func_ov015_02074b24(void);
extern void WH_SetReceiver(void (*receiver)(u16 aid, u16 *data, u16 size));
extern void ReceiveChildCardData(u16 aid, u16 *data, u16 size);
extern u16 WM_GetNextTgid(void);
extern BOOL WH_ParentConnect(int mode, u16 tgid, u16 channel);
extern void func_ov015_02072ee4(char nextState);

void UpdateWirelessParentState(void)
{
    u16 channel;

    switch (GetPanelTransitionMode()) {
    case 9:
    case 10:
        func_ov015_02072ee4(3);
        break;
    case 1:
        BeginWirelessChannelMeasurement();
        break;
    case 7:
        channel = func_ov015_02074b24();
        WH_SetReceiver(ReceiveChildCardData);
        if (WH_ParentConnect(0, WM_GetNextTgid(), channel)) {
            func_ov015_02072ee4(6);
        } else {
            func_ov015_02072ee4(3);
        }
        break;
    }
}
