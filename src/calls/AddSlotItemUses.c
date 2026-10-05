#include "nitro/types.h"

typedef struct SelectionSlot {
    u8 pad_00[4];
    u8 uses;
    u8 pad_05[7];
} SelectionSlot;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x2b];
    SelectionSlot slots[1];
} OverlaySelectionRecord;

extern int FindSlotByActiveOrder(int targetOrder);
extern u16 RefillSlotItemUses(int index);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

int AddSlotItemUses(int order)
{
    int slot = FindSlotByActiveOrder(order);
    int amount;

    if (slot < 0) {
        amount = -1;
    } else {
        amount = (s16)RefillSlotItemUses(slot);
    }
    if (amount > 0) {
        SelectionSlot *entry = &GetOverlaySelectionRecord(0)->slots[order];
        entry->uses += (u8)amount;
        amount = entry->uses;
    }
    return amount;
}
