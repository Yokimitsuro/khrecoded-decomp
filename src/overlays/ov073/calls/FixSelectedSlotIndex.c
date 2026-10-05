#include "nitro/types.h"

typedef struct SaveData {
    u8 pad_0000[0x28d7];
    u8 slotIndex : 4;
    u8 slotFilled : 4;
} SaveData;

typedef struct SlotEntry {
    u8 pad_00[4];
    void *item;
    u8 pad_08[8];
} SlotEntry;

typedef struct StatusMenu {
    u8 pad_0000[0x10f4];
    s16 slotCount;
} StatusMenu;

extern SaveData *data_0205fe0c;

void FixSelectedSlotIndex(StatusMenu *menu, SlotEntry *slots)
{
    int count;
    int i;

    if (slots[data_0205fe0c->slotIndex].item == NULL) {
        i = 0;
        count = menu->slotCount;
        for (; i < count; i++) {
            if (slots[i].item != NULL) {
                break;
            }
        }
        if (i == count) {
            i = 0xf;
        }
        data_0205fe0c->slotIndex = i;
        data_0205fe0c->slotFilled = 0;
    }
}
