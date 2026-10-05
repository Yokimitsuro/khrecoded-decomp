#include "nitro/types.h"

typedef struct MenuItem {
    u8 pad_00[8];
    int itemId;
    u8 pad_0c[8];
    int assignedSlot;
    u8 pad_18[0x24];
} MenuItem;

typedef struct FieldMenu {
    u8 pad_000[0xac];
    MenuItem *items;
    u8 pad_0b0[0x1c];
    int itemCount;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

BOOL IsMenuItemAssigned(int itemId)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    int i;
    MenuItem *item;

    for (i = 0; i < menu->itemCount; i++) {
        item = &menu->items[i];
        if (item->itemId == itemId) {
            break;
        }
    }
    if (item->assignedSlot != -1) {
        return TRUE;
    }
    return FALSE;
}
