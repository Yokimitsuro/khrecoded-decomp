#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x4a06c];
    BOOL tutorialFlagPending;
} SlotMenu;

extern void func_ov076_020c4ec8(SlotMenu *menu);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern BOOL func_ov076_020c505c(SlotMenu *menu);
extern void func_ov076_020c4280(SlotMenu *menu, int markMode, BOOL markFilledPairs);

void SlotMenu_BeginSlotSelection(SlotMenu *menu)
{
    BOOL markFilledPairs;

    func_ov076_020c4ec8(menu);
    if (!IsGlobalPackedBitSet(0xf78) && func_ov076_020c505c(menu)) {
        markFilledPairs = TRUE;
    } else {
        markFilledPairs = FALSE;
    }
    func_ov076_020c4280(menu, 0, markFilledPairs);
    menu->tutorialFlagPending = TRUE;
}
