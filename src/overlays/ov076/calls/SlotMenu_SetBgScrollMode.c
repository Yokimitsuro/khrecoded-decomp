#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x49858];
    u8 scrollMode;
} SlotMenu;

extern void func_ov076_020c7a7c(SlotMenu *menu, int mode);
extern void SlotMenu_UpdateItemSprites(SlotMenu *menu, int mode, int scrollY);

void SlotMenu_SetBgScrollMode(SlotMenu *menu, int mode, int scrollY)
{
    menu->scrollMode = mode;
    if (mode != 0) {
        *(volatile u32 *)0x04000018 = ((scrollY - 0x18) << 16) & 0x1ff0000;
    } else {
        *(volatile u32 *)0x04000018 = (((scrollY - 0x18) << 16) & 0x1ff0000) | 0x1e8;
    }
    func_ov076_020c7a7c(menu, mode);
    SlotMenu_UpdateItemSprites(menu, mode, scrollY);
}
