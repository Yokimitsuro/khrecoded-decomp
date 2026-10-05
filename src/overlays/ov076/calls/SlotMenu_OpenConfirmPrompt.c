#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void func_ov076_020c4ec8(SlotMenu *menu);
extern void SlotMenu_SelectGuideStep(SlotMenu *menu);
extern void SlotMenu_OpenSlotMessage(SlotMenu *menu, int messageId);

void SlotMenu_OpenConfirmPrompt(SlotMenu *menu)
{
    func_ov076_020c4ec8(menu);
    SlotMenu_SelectGuideStep(menu);
    SlotMenu_OpenSlotMessage(menu, 0x27);
    menu->state = 3;
}
