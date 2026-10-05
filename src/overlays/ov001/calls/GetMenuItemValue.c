#include "nitro/types.h"

typedef struct MenuItem {
    u8 pad_00[0x14];
    int value;
} MenuItem;

typedef struct MenuItemTable {
    u8 pad_00[8];
    MenuItem *items[1];
} MenuItemTable;

typedef struct MenuContext {
    MenuItemTable *table;
    u8 pad_0004[0x10bc];
    s8 selectedIndex;
    u8 pad_10C1[3];
    int selectedCount;
} MenuContext;

extern MenuContext *data_ov001_020a048c;

int GetMenuItemValue(int index)
{
    MenuContext *menu = data_ov001_020a048c;
    MenuItem *item = menu->table->items[index];

    if (index == menu->selectedIndex) {
        return menu->selectedCount * 5;
    }
    return item->value;
}
