#include "nitro/types.h"

typedef struct ItemEntry {
    u8 pad_00[8];
    void *info;
} ItemEntry;

typedef struct ItemSlot {
    u8 pad_00[4];
    ItemEntry *entry;
} ItemSlot;

typedef struct ItemMenu {
    u8 pad_00[2];
    u8 useCatalog;
    u8 pad_03[0x36a1];
    ItemEntry *catalog[0x8ea];
    ItemSlot *slots[1];
} ItemMenu;

void *GetItemMenuEntryInfo(ItemMenu *menu, int index)
{
    if (menu->useCatalog) {
        return menu->catalog[(u16)index]->info;
    }
    return menu->slots[index]->entry->info;
}
