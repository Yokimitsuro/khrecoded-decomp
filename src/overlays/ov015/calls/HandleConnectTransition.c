#include "nitro/types.h"

extern u32 GetPanelTransitionMode(void);
extern void func_ov015_02072ee4(char nextState);
extern void WH_SetReceiver(void (*receiver)(u16 aid, u16 *data, u16 size));
extern void ReceivePeerCardData(u16 aid, u16 *data, u16 size);
extern int func_ov015_02073d68(int mode, int arg1, int arg2);

void HandleConnectTransition(void)
{
    switch (GetPanelTransitionMode()) {
    case 9:
    case 10:
        func_ov015_02072ee4(3);
        break;
    case 1:
        WH_SetReceiver(ReceivePeerCardData);
        if (func_ov015_02073d68(1, 0, 0) != 0) {
            func_ov015_02072ee4(7);
        } else {
            func_ov015_02072ee4(3);
        }
        break;
    }
}
