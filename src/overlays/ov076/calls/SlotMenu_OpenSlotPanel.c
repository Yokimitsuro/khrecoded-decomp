#include "nitro/types.h"

typedef struct ScreenPos {
    u8 pad_00[4];
    s16 x;
    s16 y;
    u8 pad_08[4];
} ScreenPos;

typedef struct SlotMenu {
    s32 state;
    u8 pad_00004[0x10];
    s32 column;
    u8 pad_00018[0xc];
    u8 panel[0x11ee6 - 0x24];
    s16 slotIndex;
} SlotMenu;

extern ScreenPos data_ov076_020cd2ec;
extern ScreenPos data_ov076_020cd2f8;

extern void func_ov076_020c5318(SlotMenu *menu, u16 slot, u16 column, int mode, ScreenPos *pos);
extern BOOL func_ov076_020cbbc0(void *panel, SlotMenu *owner, int (*getValue)(int *), void (*onClose)(SlotMenu *), ScreenPos *pos, int style);
extern int func_ov076_020c5264(int *p);
extern void func_ov076_020c4ec8(SlotMenu *menu);
extern void *func_ov039_020bc1dc(void);
extern void SetNavigationElementsVisible(void *container, BOOL visible);

void SlotMenu_OpenSlotPanel(SlotMenu *menu)
{
    func_ov076_020c5318(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2ec);
    func_ov076_020c5318(menu, menu->slotIndex, menu->column, 0, &data_ov076_020cd2f8);
    if (func_ov076_020cbbc0(menu->panel, menu, func_ov076_020c5264, func_ov076_020c4ec8, &data_ov076_020cd2ec, 2)) {
        menu->state = 2;
        SetNavigationElementsVisible(func_ov039_020bc1dc(), FALSE);
    }
}
