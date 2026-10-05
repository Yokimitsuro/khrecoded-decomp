#include "nitro/types.h"

typedef struct SelectionSlot {
    s16 itemId;
    u8 pad_02[2];
    u8 uses;
    u8 pad_05[7];
} SelectionSlot;

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_001[0x2b];
    SelectionSlot slots[1];
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

int GetConsumableSlotUses(int index)
{
    int uses = -1;
    SelectionSlot *slot = &GetOverlaySelectionRecord(0)->slots[index];

    switch (slot->itemId) {
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
        uses = slot->uses;
        break;
    }
    return uses;
}
