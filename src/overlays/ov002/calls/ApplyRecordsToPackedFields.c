#include "nitro/types.h"

typedef struct PackedFields {
    u32 field6 : 5;
    u32 field17 : 5;
    u32 field12 : 6;
    u32 field20 : 7;
    u32 field21 : 7;
    u32 pad0 : 2;
    u32 field0 : 4;
    u32 field1 : 4;
    u32 field3 : 8;
    u32 field4 : 5;
    u32 field5 : 5;
    u32 field2 : 6;
    u32 field7 : 7;
    u32 field8 : 7;
    u32 field9 : 7;
    u32 field10 : 7;
    u32 field15 : 4;
    u32 field11 : 7;
    u32 field16 : 7;
    u32 field13 : 6;
    u32 field19 : 5;
    u32 field14 : 5;
    u32 pad3 : 2;
} PackedFields;

typedef struct RecordB {
    u8 pad_00[0x4];
    s32 valid;
    s32 itemId;
    s32 category;
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
} RecordB;

extern s32 data_ov002_0206aebc[];
extern BOOL IsRecordSlotAcquired(s32 slot);
extern int AcquireRecordSlot(int slot, int param);
extern void ReleaseRecordSlot(s32 slot);
extern RecordB *GetRecordTableBEntry(s32 index);
extern int LookupTableOffset(int index, int offset);

BOOL ApplyRecordsToPackedFields(PackedFields *fields, s32 *recordIds, int count)
{
    RecordB *linked[22];
    RecordB *entry;
    RecordB *other;
    s32 recordId;
    s32 category;
    u32 value;
    s32 offset;
    int n;
    int i;
    BOOL acquired;

    acquired = IsRecordSlotAcquired(9);
    if (!acquired) {
        AcquireRecordSlot(9, 1);
    }
    for (n = 0; n < count; n++) {
        recordId = recordIds[n];
        if (recordId == -1 || recordId >= 0x5a1) {
            break;
        }
        entry = GetRecordTableBEntry(recordId);
        if (entry->valid == 0 || (category = entry->category) <= 0) {
            continue;
        }
        if (category == 0x13 || category >= 0x15) {
            continue;
        }
        for (i = 0; i < 22; i++) {
            value = -1;
            linked[i] = NULL;
            switch (i) {
            case 3: value = fields->field3; break;
            case 4: value = fields->field4; break;
            case 5: value = fields->field5; break;
            case 6: value = fields->field6; break;
            case 7: value = fields->field7; break;
            case 8: value = fields->field8; break;
            case 9: value = fields->field9; break;
            case 10: value = fields->field10; break;
            case 11: value = fields->field11; break;
            case 12: value = fields->field12; break;
            case 13: value = fields->field13; break;
            case 14: value = fields->field14; break;
            case 15: value = fields->field15; break;
            case 16: value = fields->field16; break;
            case 17: value = fields->field17; break;
            case 19: value = fields->field19; break;
            case 20: value = fields->field20; break;
            case 21: value = fields->field21; break;
            }
            offset = value - 1;
            if (offset >= 0) {
                linked[i] = GetRecordTableBEntry(LookupTableOffset(i, offset));
            }
        }
        for (i = 0; i < 22; i++) {
            if ((other = linked[i]) == NULL) {
                continue;
            }
            if ((entry->slot0 & other->slot0) || (entry->slot1 & other->slot1) ||
                (entry->slot2 & other->slot2) || (entry->slot3 & other->slot3) ||
                (entry->slot4 & other->slot4) || (entry->slot5 & other->slot5) ||
                (entry->slot6 & other->slot6) || (entry->slot7 & other->slot7) ||
                (entry->slot8 & other->slot8) || (entry->slot9 & other->slot9) ||
                (entry->slot10 & other->slot10) || (entry->slot11 & other->slot11) ||
                (entry->slot12 & other->slot12) || (entry->slot13 & other->slot13) ||
                (entry->slot14 & other->slot14) || (entry->slot15 & other->slot15)) {
                switch (i) {
                case 3: fields->field3 = 0; break;
                case 4: fields->field4 = 0; break;
                case 5: fields->field5 = 0; break;
                case 6: fields->field6 = 0; break;
                case 7: fields->field7 = 0; break;
                case 8: fields->field8 = 0; break;
                case 9: fields->field9 = 0; break;
                case 10: fields->field10 = 0; break;
                case 11: fields->field11 = 0; break;
                case 12: fields->field12 = 0; break;
                case 13: fields->field13 = 0; break;
                case 14: fields->field14 = 0; break;
                case 15: fields->field15 = 0; break;
                case 17: fields->field17 = 0; break;
                case 19: fields->field19 = 0; break;
                case 16: fields->field16 = 0; break;
                case 20: fields->field20 = 0; break;
                case 21: fields->field21 = 0; break;
                }
                linked[i] = NULL;
            }
        }
        if (entry->slot0) {
            fields->field3 = 0;
        }
        if (entry->slot1) {
            fields->field4 = 0;
        }
        if (entry->slot2) {
            fields->field5 = 0;
        }
        if (entry->slot3) {
            fields->field6 = 0;
        }
        if (entry->slot4) {
            fields->field8 = 0;
        }
        if (entry->slot5) {
            fields->field9 = 0;
        }
        if (entry->slot6) {
            fields->field10 = 0;
        }
        if (entry->slot7) {
            fields->field11 = 0;
        }
        if (entry->slot8) {
            fields->field12 = 0;
        }
        if (entry->slot9) {
            fields->field13 = 0;
        }
        if (entry->slot10) {
            fields->field14 = 0;
        }
        if (entry->slot11) {
            fields->field15 = 0;
        }
        if (entry->slot12) {
            if (linked[16] != NULL && linked[16]->slot12) {
                fields->field16 = 0;
            }
            if (linked[20] != NULL && linked[20]->slot12) {
                fields->field20 = 0;
            }
            if (linked[21] != NULL && linked[21]->slot12) {
                fields->field21 = 0;
            }
        }
        if (entry->slot13) {
            if (linked[16] != NULL && linked[16]->slot13) {
                fields->field16 = 0;
            }
            if (linked[20] != NULL && linked[20]->slot13) {
                fields->field20 = 0;
            }
            if (linked[21] != NULL && linked[21]->slot13) {
                fields->field21 = 0;
            }
        }
        if (entry->slot14) {
            if (linked[16] != NULL && linked[16]->slot14) {
                fields->field16 = 0;
            }
            if (linked[20] != NULL && linked[20]->slot14) {
                fields->field20 = 0;
            }
            if (linked[21] != NULL && linked[21]->slot14) {
                fields->field21 = 0;
            }
        }
        if (entry->slot15) {
            fields->field19 = 0;
        }
        value = recordId - data_ov002_0206aebc[category - 1] + 1;
        switch (category) {
        case 1: fields->field0 = value; break;
        case 2: fields->field1 = value; break;
        case 3: fields->field2 = value; break;
        case 4: fields->field3 = value; break;
        case 5: fields->field4 = value; break;
        case 6: fields->field5 = value; break;
        case 7: fields->field6 = value; break;
        case 8: fields->field7 = value; break;
        case 9: fields->field8 = value; break;
        case 10: fields->field9 = value; break;
        case 11: fields->field10 = value; break;
        case 12: fields->field11 = value; break;
        case 13: fields->field12 = value; break;
        case 14: fields->field13 = value; break;
        case 15: fields->field14 = value; break;
        case 16: fields->field15 = value; break;
        case 17:
            if (fields->field16 == 0) {
                fields->field16 = value;
            } else if (fields->field20 == 0) {
                fields->field20 = value;
            } else if (fields->field21 == 0) {
                fields->field21 = value;
            }
            break;
        case 18: fields->field17 = value; break;
        case 20: fields->field19 = value; break;
        }
    }
    if (!acquired) {
        ReleaseRecordSlot(9);
    }
    return TRUE;
}
