#include "nitro/types.h"

typedef struct SelectionEntry {
    u8 pad_00[4];
    u8 count;
    u8 pad_05[7];
} SelectionEntry;

typedef struct OverlaySelectionRecord {
    u8 pad_00[0x2c];
    SelectionEntry entries[1];
} OverlaySelectionRecord;

extern int FindSlotByActiveOrder(int targetOrder);
extern int func_0202947c(int index);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);

u8 UpdateSelectionCount(int order)
{
    SelectionEntry *entry;
    int count;
    int slot = FindSlotByActiveOrder(order);

    if (slot < 0) {
        count = -1;
    } else {
        count = func_0202947c(slot);
    }
    entry = &GetOverlaySelectionRecord(0)->entries[order];
    if (count >= 0) {
        entry->count = count;
    } else {
        entry->count--;
    }
    return entry->count;
}
