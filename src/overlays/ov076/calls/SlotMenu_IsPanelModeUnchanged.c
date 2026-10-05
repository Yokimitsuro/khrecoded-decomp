#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x24];
    u8 panel[0x11ebc];
    s32 panelMode;
} SlotMenu;

extern BOOL func_ov039_020bc0f4(void);
extern int func_ov076_020cc35c(void *panel);

BOOL SlotMenu_IsPanelModeUnchanged(SlotMenu *menu)
{
    int mode;

    if (!func_ov039_020bc0f4()) {
        return TRUE;
    }
    mode = func_ov076_020cc35c(menu->panel);
    if (menu->panelMode == mode) {
        return TRUE;
    }
    menu->panelMode = mode;
    return FALSE;
}
