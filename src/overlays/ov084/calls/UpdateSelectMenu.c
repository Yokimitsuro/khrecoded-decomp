#include "nitro/types.h"

typedef struct SelectMenu {
    u8 selection;
    u8 enabledMask;
    u8 dirty;
} SelectMenu;

extern void RefreshSelectButtons(SelectMenu *menu);
extern void func_ov084_020bfa64(SelectMenu *menu);
extern void DrawSelectMenuModel(SelectMenu *menu);

void UpdateSelectMenu(SelectMenu *menu)
{
    if (menu->dirty != 0) {
        RefreshSelectButtons(menu);
        func_ov084_020bfa64(menu);
        menu->dirty--;
    }
    DrawSelectMenuModel(menu);
}
