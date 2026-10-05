#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x4a06c];
    s32 hasEquippedSlots;
} SlotMenu;

extern BOOL IsGlobalPackedBitSet(int bit);
extern BOOL func_ov076_020c5108(SlotMenu *menu);
extern BOOL SlotMenu_HasFullyRankedSlot(SlotMenu *menu);
extern void SlotMenu_BuildSlotMasks(SlotMenu *menu, int step, BOOL extra);

void SlotMenu_SelectGuideStep(SlotMenu *menu)
{
    int step = -1;
    BOOL extra;

    if (IsGlobalPackedBitSet(0xf75) && menu->hasEquippedSlots != 0) {
        step = 0;
    } else if (!IsGlobalPackedBitSet(0xf79)) {
        if (func_ov076_020c5108(menu)) {
            step = 1;
        }
    } else if (!IsGlobalPackedBitSet(0xf78)) {
        if (SlotMenu_HasFullyRankedSlot(menu)) {
            step = 2;
        }
    }
    if (step == 0 && !IsGlobalPackedBitSet(0xf78) && SlotMenu_HasFullyRankedSlot(menu)) {
        extra = TRUE;
    } else {
        extra = FALSE;
    }
    SlotMenu_BuildSlotMasks(menu, step, extra);
}
