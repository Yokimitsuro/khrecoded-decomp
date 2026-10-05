#include "nitro/types.h"

typedef struct Panel {
    u8 pad_00[0x4c];
    s32 usedSlotCount;
    s32 cursorIndex;
    u8 pad_54[0x6688 - 0x54];
    BOOL progressFlag;
    u8 pad_668c[0x66c4 - 0x668c];
    u32 unlockFlagA;
    u32 unlockFlagB;
} Panel;

extern u32 data_0205fe20;

extern void SetPanelFlag(Panel *panel, int bit, BOOL enable);
extern void SetGlobalPackedBit(int bitIndex);

void ApplyPanelMenuFlags(Panel *panel, BOOL selectContinue)
{
    int i;

    for (i = 0; i < 4; i++) {
        SetPanelFlag(panel, i, TRUE);
    }

    if (panel->usedSlotCount == 0) {
        panel->cursorIndex = 0;
        data_0205fe20 = 0;
        SetPanelFlag(panel, 1, FALSE);
        SetPanelFlag(panel, 2, FALSE);
        SetPanelFlag(panel, 3, FALSE);
        return;
    }

    if (selectContinue) {
        panel->cursorIndex = 1;
    }
    data_0205fe20 = 1;
    if (!panel->progressFlag) {
        SetPanelFlag(panel, 3, FALSE);
    }
    if (panel->unlockFlagA) {
        SetGlobalPackedBit(0x1150);
    }
    if (panel->unlockFlagB) {
        SetGlobalPackedBit(0x1151);
    }
    if (panel->progressFlag) {
        SetGlobalPackedBit(0xbea);
    }
}
