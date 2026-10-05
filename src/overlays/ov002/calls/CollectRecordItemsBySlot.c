#include "nitro/types.h"

typedef struct RecordB {
    u8 pad_00[0x8];
    s32 itemId;
    u8 pad_0C[0x4];
    u16 slot0 : 1;
    u16 slot1 : 1;
    u16 slot2 : 1;
    u16 slot3 : 1;
    u16 slot4 : 1;
    u16 slot5 : 1;
    u16 slot6 : 1;
    u16 slot7 : 1;
    u16 slot8 : 1;
    u16 slot9 : 1;
    u16 slot10 : 1;
    u16 slot11 : 1;
    u16 slot12 : 1;
    u16 slot13 : 1;
    u16 slot14 : 1;
    u16 slot15 : 1;
    u8 pad_12[0x6];
} RecordB;

extern void MI_CpuFill8(void *dest, int value, u32 size);
extern s32 GetPackedFieldValue(void *fields, int fieldIndex, BOOL raw);
extern int LookupTableOffset(int index, int offset);
extern RecordB *GetRecordTableBEntry(s32 index);

void CollectRecordItemsBySlot(void *fields, s32 *itemIds)
{
    int field;
    int slot;
    s32 value;
    RecordB *record;

    MI_CpuFill8(itemIds, 0xff, 0x40);
    for (field = 0; field < 0x16; field++) {
        slot = 0;
        value = GetPackedFieldValue(fields, field, FALSE);
        if (value < 0) {
            continue;
        }
        record = GetRecordTableBEntry(LookupTableOffset(field, value));
        for (; slot < 0x10; slot++) {
            switch (slot) {
            case 0: if (!record->slot0) continue; break;
            case 1: if (!record->slot1) continue; break;
            case 2: if (!record->slot2) continue; break;
            case 3: if (!record->slot3) continue; break;
            case 4: if (!record->slot4) continue; break;
            case 5: if (!record->slot5) continue; break;
            case 6: if (!record->slot6) continue; break;
            case 7: if (!record->slot7) continue; break;
            case 8: if (!record->slot8) continue; break;
            case 9: if (!record->slot9) continue; break;
            case 10: if (!record->slot10) continue; break;
            case 11: if (!record->slot11) continue; break;
            case 12: if (!record->slot12) continue; break;
            case 13: if (!record->slot13) continue; break;
            case 14: if (!record->slot14) continue; break;
            case 15: if (!record->slot15) continue; break;
            }
            itemIds[slot] = record->itemId;
        }
    }
}
