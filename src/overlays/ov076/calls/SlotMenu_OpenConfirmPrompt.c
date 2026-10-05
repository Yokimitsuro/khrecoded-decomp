#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void func_ov076_020c4ec8(SlotMenu *menu);
extern void func_ov076_020c43bc(SlotMenu *menu);
extern void func_ov076_020c83a8(SlotMenu *menu, int messageId);

void SlotMenu_OpenConfirmPrompt(SlotMenu *menu)
{
    func_ov076_020c4ec8(menu);
    func_ov076_020c43bc(menu);
    func_ov076_020c83a8(menu, 0x27);
    menu->state = 3;
}
