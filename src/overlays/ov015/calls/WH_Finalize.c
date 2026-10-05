#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x40];
    int connectMode;
    u8 pad_44[0xc];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207fbc0[];
extern void SetPanelTransitionMode(int state);
extern void PollPanelTransition(void);
extern BOOL EndWirelessScan(void);
extern BOOL func_ov015_020745dc(void);
extern int ClearSlotEventHandler(void *dataSharingInfo);
extern BOOL func_ov015_02074634(void);
extern BOOL WH_EndChildStep(void);
extern BOOL func_ov015_02073cbc(void);

void WH_Finalize(void)
{
    if (data_ov015_0207e980.sysState == 1) {
        return;
    }

    if (data_ov015_0207e980.sysState == 2) {
        if (!EndWirelessScan()) {
            PollPanelTransition();
        }
        return;
    }

    if (data_ov015_0207e980.sysState != 6 && data_ov015_0207e980.sysState != 5 && data_ov015_0207e980.sysState != 4) {
        SetPanelTransitionMode(3);
        PollPanelTransition();
        return;
    }

    SetPanelTransitionMode(3);

    switch (data_ov015_0207e980.connectMode) {
    case 3:
        if (!func_ov015_020745dc()) {
            PollPanelTransition();
        }
        break;
    case 5:
        if (ClearSlotEventHandler(data_ov015_0207fbc0) != 0) {
            PollPanelTransition();
            break;
        }
    case 1:
        if (!func_ov015_02074634()) {
            PollPanelTransition();
        }
        break;
    case 2:
        if (!WH_EndChildStep()) {
            PollPanelTransition();
        }
        break;
    case 4:
        if (ClearSlotEventHandler(data_ov015_0207fbc0) != 0) {
            PollPanelTransition();
            break;
        }
    case 0:
        if (!func_ov015_02073cbc()) {
            PollPanelTransition();
        }
        break;
    }
}
