#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct SaveData {
    u8 pad_0000[0x2d84];
    u16 slotHandles[16];
} SaveData;

typedef struct SlotMenu {
    u8 pad_00000[0x497f8];
    RecordEntry records[8];
} SlotMenu;

extern SaveData *data_0205fe0c;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

BOOL SlotMenu_CanCombineSlotPair(SlotMenu *menu, int slot)
{
    int pairIndex = slot * 2;
    u16 first = data_0205fe0c->slotHandles[pairIndex];
    u16 second = data_0205fe0c->slotHandles[pairIndex + 1];
    RecordEntry *recordA;
    RecordEntry *recordB;

    if (first >= 0x200 && first < 0x458 && second >= 0x200 && second < 0x458) {
        recordA = GetActiveRecordEntryOrNull((u16)(first - 0x200));
        recordB = GetActiveRecordEntryOrNull((u16)(second - 0x200));
        if (recordA->variant != 0 && recordB->variant != 0
            && (recordA->level != 100 || recordA->kind != 3 || recordA->category != menu->records[slot].category)) {
            return TRUE;
        }
        return FALSE;
    }
    return FALSE;
}
