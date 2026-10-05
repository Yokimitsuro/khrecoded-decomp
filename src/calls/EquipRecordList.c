#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s32 enabled;
    u8 pad_08[4];
    s32 category;
    u16 blocksSlot4 : 1;
    u16 blocksSlot5 : 1;
    u16 blocksSlot6 : 1;
    u16 blocksSlot7 : 1;
    u16 blocksSlot9 : 1;
    u16 blocksSlot10 : 1;
    u16 blocksSlot11 : 1;
    u16 blocksSlot12 : 1;
    u16 blocksSlot13 : 1;
    u16 blocksSlot14 : 1;
    u16 blocksSlot15 : 1;
    u16 blocksSlot16 : 1;
    u16 blocksSlot17A : 1;
    u16 blocksSlot17B : 1;
    u16 blocksSlot17C : 1;
    u16 blocksSlot20 : 1;
} RecordB;

typedef struct {
    u32 slot7 : 5;
    u32 slot18 : 5;
    u32 slot13 : 6;
    u32 unk_00 : 16;
    u32 slot1 : 4;
    u32 slot2 : 4;
    u32 slot4 : 8;
    u32 slot5 : 5;
    u32 slot6 : 5;
    u32 slot3 : 6;
    u32 slot8 : 7;
    u32 slot9 : 7;
    u32 slot10 : 7;
    u32 slot11 : 7;
    u32 slot16 : 4;
    u32 slot12 : 7;
    u32 slot17 : 7;
    u32 slot14 : 6;
    u32 slot20 : 5;
    u32 slot15 : 5;
    u32 unk_0C : 2;
} EquipSlots;

typedef struct {
    u8 pad_00[0x276c];
    EquipSlots slots;
} SaveData;

typedef struct {
    u8 pad_00[0xc];
    SaveData *data;
} MainDataHolder_0205fe00;

extern RecordB *GetRecordTableBEntry(s32 index);
extern MainDataHolder_0205fe00 data_0205fe00;
extern s32 data_02053530[];

BOOL EquipRecordList(s32 *recordIndices, s32 count)
{
    EquipSlots *slots = &data_0205fe00.data->slots;
    s32 recordIndex;
    RecordB *record;
    s32 i;
    RecordB *equipped[21];

    for (i = 0; i < count; i++) {
        s32 category;
        s32 slot;

        recordIndex = recordIndices[i];
        if (recordIndex == -1 || recordIndex >= 0x5a1) {
            break;
        }
        record = GetRecordTableBEntry(recordIndex);
        if (record->enabled == 0) {
            continue;
        }
        category = record->category;
        if (category <= 0 || category == 19 || category >= 21) {
            continue;
        }

        for (slot = 0; slot < 21; slot++) {
            s32 value = -1;
            s32 offset;

            equipped[slot] = NULL;
            switch (slot) {
            case 4:
                value = slots->slot4;
                break;
            case 5:
                value = slots->slot5;
                break;
            case 6:
                value = slots->slot6;
                break;
            case 7:
                value = slots->slot7;
                break;
            case 8:
                value = slots->slot8;
                break;
            case 9:
                value = slots->slot9;
                break;
            case 10:
                value = slots->slot10;
                break;
            case 11:
                value = slots->slot11;
                break;
            case 12:
                value = slots->slot12;
                break;
            case 13:
                value = slots->slot13;
                break;
            case 14:
                value = slots->slot14;
                break;
            case 15:
                value = slots->slot15;
                break;
            case 16:
                value = slots->slot16;
                break;
            case 17:
                value = slots->slot17;
                break;
            case 18:
                value = slots->slot18;
                break;
            case 20:
                value = slots->slot20;
                break;
            }
            offset = value - 1;
            if (offset >= 0) {
                s32 entryIndex = data_02053530[slot - 1];
                if (entryIndex != -1) {
                    entryIndex += offset;
                }
                equipped[slot] = GetRecordTableBEntry(entryIndex);
            }
        }

        for (slot = 0; slot < 21; slot++) {
            RecordB *other = equipped[slot];
            if (other == NULL) {
                continue;
            }
            switch (category) {
            case 4:
                if (!other->blocksSlot4) {
                    continue;
                }
                break;
            case 5:
                if (!other->blocksSlot5) {
                    continue;
                }
                break;
            case 6:
                if (!other->blocksSlot6) {
                    continue;
                }
                break;
            case 7:
                if (!other->blocksSlot7) {
                    continue;
                }
                break;
            case 9:
                if (!other->blocksSlot9) {
                    continue;
                }
                break;
            case 10:
                if (!other->blocksSlot10) {
                    continue;
                }
                break;
            case 11:
                if (!other->blocksSlot11) {
                    continue;
                }
                break;
            case 12:
                if (!other->blocksSlot12) {
                    continue;
                }
                break;
            case 13:
                if (!other->blocksSlot13) {
                    continue;
                }
                break;
            case 14:
                if (!other->blocksSlot14) {
                    continue;
                }
                break;
            case 15:
                if (!other->blocksSlot15) {
                    continue;
                }
                break;
            case 16:
                if (!other->blocksSlot16) {
                    continue;
                }
                break;
            case 17:
                if (!other->blocksSlot17A && !other->blocksSlot17B && !other->blocksSlot17C) {
                    continue;
                }
                break;
            case 20:
                if (!other->blocksSlot20) {
                    continue;
                }
                break;
            default:
                continue;
            }
            switch (slot) {
            case 4:
                slots->slot4 = 0;
                break;
            case 5:
                slots->slot5 = 0;
                break;
            case 6:
                slots->slot6 = 0;
                break;
            case 7:
                slots->slot7 = 0;
                break;
            case 8:
                slots->slot8 = 0;
                break;
            case 9:
                slots->slot9 = 0;
                break;
            case 10:
                slots->slot10 = 0;
                break;
            case 11:
                slots->slot11 = 0;
                break;
            case 12:
                slots->slot12 = 0;
                break;
            case 13:
                slots->slot13 = 0;
                break;
            case 14:
                slots->slot14 = 0;
                break;
            case 15:
                slots->slot15 = 0;
                break;
            case 16:
                slots->slot16 = 0;
                break;
            case 17:
                slots->slot17 = 0;
                break;
            case 18:
                slots->slot18 = 0;
                break;
            case 20:
                slots->slot20 = 0;
                break;
            }
            equipped[slot] = NULL;
        }

        if (record->blocksSlot4) {
            slots->slot4 = 0;
        }
        if (record->blocksSlot5) {
            slots->slot5 = 0;
        }
        if (record->blocksSlot6) {
            slots->slot6 = 0;
        }
        if (record->blocksSlot7) {
            slots->slot7 = 0;
        }
        if (record->blocksSlot9) {
            slots->slot9 = 0;
        }
        if (record->blocksSlot10) {
            slots->slot10 = 0;
        }
        if (record->blocksSlot11) {
            slots->slot11 = 0;
        }
        if (record->blocksSlot12) {
            slots->slot12 = 0;
        }
        if (record->blocksSlot13) {
            slots->slot13 = 0;
        }
        if (record->blocksSlot14) {
            slots->slot14 = 0;
        }
        if (record->blocksSlot15) {
            slots->slot15 = 0;
        }
        if (record->blocksSlot16) {
            slots->slot16 = 0;
        }
        if (record->blocksSlot17A || record->blocksSlot17B || record->blocksSlot17C) {
            slots->slot17 = 0;
        }
        if (record->blocksSlot20) {
            slots->slot20 = 0;
        }

        {
            s32 value = recordIndex - data_02053530[category - 1] + 1;
            switch (category) {
            case 1:
                slots->slot1 = value;
                break;
            case 2:
                slots->slot2 = value;
                break;
            case 3:
                slots->slot3 = value;
                break;
            case 4:
                slots->slot4 = value;
                break;
            case 5:
                slots->slot5 = value;
                break;
            case 6:
                slots->slot6 = value;
                break;
            case 7:
                slots->slot7 = value;
                break;
            case 8:
                slots->slot8 = value;
                break;
            case 9:
                slots->slot9 = value;
                break;
            case 10:
                slots->slot10 = value;
                break;
            case 11:
                slots->slot11 = value;
                break;
            case 12:
                slots->slot12 = value;
                break;
            case 13:
                slots->slot13 = value;
                break;
            case 14:
                slots->slot14 = value;
                break;
            case 15:
                slots->slot15 = value;
                break;
            case 16:
                slots->slot16 = value;
                break;
            case 17:
                slots->slot17 = value;
                break;
            case 18:
                slots->slot18 = value;
                break;
            case 20:
                slots->slot20 = value;
                break;
            }
        }
    }
    return TRUE;
}
