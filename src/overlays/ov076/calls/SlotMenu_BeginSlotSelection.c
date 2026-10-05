#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x4a06c];
    BOOL tutorialFlagPending;
} SlotMenu;

extern void func_ov076_020c4ec8(SlotMenu *menu);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern BOOL SlotMenu_HasFullyRankedSlot(SlotMenu *menu);
extern void SlotMenu_BuildSlotMasks(SlotMenu *menu, int markMode, BOOL markFilledPairs);

void SlotMenu_BeginSlotSelection(SlotMenu *menu)
{
    BOOL markFilledPairs;

    func_ov076_020c4ec8(menu);
    if (!IsGlobalPackedBitSet(0xf78) && SlotMenu_HasFullyRankedSlot(menu)) {
        markFilledPairs = TRUE;
    } else {
        markFilledPairs = FALSE;
    }
    SlotMenu_BuildSlotMasks(menu, 0, markFilledPairs);
    menu->tutorialFlagPending = TRUE;
}
