#include "nitro/types.h"

typedef struct WirelessHelper {
    u8 pad_00[8];
    u16 measuredChannel;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void SetPanelTransitionMode(u32 mode);
extern int RunTransitionSlot2(void (*callback)(void *));
extern void ChoosePanelModeFromSelection(void *context);

BOOL WH_StartTransitionStep(void)
{
    SetPanelTransitionMode(3);
    if (RunTransitionSlot2(ChoosePanelModeFromSelection) == 2) {
        data_ov015_0207e980.measuredChannel = 0;
        return TRUE;
    }
    SetPanelTransitionMode(9);
    return FALSE;
}
