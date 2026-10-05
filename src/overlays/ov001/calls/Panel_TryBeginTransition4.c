#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x30];
    s32 state;
    u8 pad_34[0x4];
    s32 inputReady;
    u8 pad_3C[0x1c];
    s32 nextState;
    u8 pad_5C[0x7c];
    s32 transitionType;
    u8 pad_DC[0x8];
    u32 slotIds[4];
} Panel;

extern Panel *data_ov001_020a04e8;
extern u32 func_ov001_0207b3f4(void);
extern u32 LookupChannelEntry(s32 index);
extern void SetDisplaySetting(int value);
extern void func_ov001_0207b234(Panel *panel, s32 transitionType);

BOOL Panel_TryBeginTransition4(void)
{
    Panel *panel;
    s32 i;

    panel = data_ov001_020a04e8;
    if (panel->state == 2) {
        return FALSE;
    }
    if (panel->transitionType == 4) {
        return FALSE;
    }
    if (panel->inputReady == 0) {
        return FALSE;
    }
    if (func_ov001_0207b3f4() == 2) {
        i = 0;
        do {
            panel->slotIds[i] = LookupChannelEntry(i);
            i++;
        } while (i < 4);
    }
    SetDisplaySetting(1);
    func_ov001_0207b234(panel, 4);
    panel->nextState = 6;
    return TRUE;
}
