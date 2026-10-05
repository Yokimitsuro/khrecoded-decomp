#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void func_ov076_020c4ec8(SlotMenu *menu);
extern void SlotMenu_BuildSlotMasks(SlotMenu *menu, int markMode, BOOL markFilledPairs);
extern void SlotMenu_LoadCursorSlotRecord(SlotMenu *menu);
extern void SlotMenu_UpdatePairedCategory(SlotMenu *menu);

#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_DISPCNT (*(vu32 *)0x04000000)

void SlotMenu_EnterSlotView(SlotMenu *menu)
{
    func_ov076_020c4ec8(menu);
    SlotMenu_BuildSlotMasks(menu, -1, FALSE);
    REG_BG1CNT = (REG_BG1CNT & 0x43) | 0x10;
    SlotMenu_LoadCursorSlotRecord(menu);
    SlotMenu_UpdatePairedCategory(menu);
    REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x1f00;
}
