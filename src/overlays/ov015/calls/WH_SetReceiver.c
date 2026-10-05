#include "nitro/types.h"

typedef void (*WhReceiverFunc)(u16 aid, u16 *data, u16 size);

typedef struct WirelessHelper {
    u8 pad_00[0x44];
    WhReceiverFunc receiver;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern int SetSlotEventHandler(int slot, void (*callback)(void *), void *arg);
extern void SetPanelTransitionMode(u32 mode);
extern void func_ov015_02074840(void *arg);

void WH_SetReceiver(WhReceiverFunc receiver)
{
    data_ov015_0207e980.receiver = receiver;
    if (SetSlotEventHandler(14, func_ov015_02074840, NULL) != 0) {
        SetPanelTransitionMode(9);
    }
}
