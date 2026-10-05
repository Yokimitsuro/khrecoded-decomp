#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
    u8 pad_2DA4[0x2dc0 - 0x2da4];
    s32 slotAmounts[8];
} SaveData;

typedef struct ItemInfo {
    u16 pad_00;
    u16 useCount;
    u8 pad_04[8];
} ItemInfo;

typedef struct SlotMenu {
    u8 pad_00000[0x81c];
    ItemInfo items[1];
} SlotMenu;

typedef struct SelectionRecord {
    u8 pad_000[0xec];
    s32 slotAmounts[8];
} SelectionRecord;

extern SaveData *data_0205fe0c;

extern SelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

void SlotMenu_UnequipSlotEntry(SlotMenu *menu, int slot, int column)
{
    int index = slot * 2 + column;
    u16 handle = data_0205fe0c->slotHandles[index];

    if (handle != 0xffff) {
        if (handle >= 0x200 && handle < 0x458) {
            ItemInfo *item = &menu->items[handle];

            item->useCount--;
        } else {
            ItemInfo *item = &menu->items[handle];

            item->useCount = item->useCount - data_0205fe0c->slotAmounts[slot];
            data_0205fe0c->slotAmounts[slot] = 0;
        }
    }
    data_0205fe0c->slotHandles[index] = 0xffff;
    GetOverlaySelectionRecord(0)->slotAmounts[slot] = 0;
}
