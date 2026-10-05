#include "nitro/types.h"

typedef struct ItemInfo {
    int id;
    u8 pad_04[0x14];
    u16 category;
} ItemInfo;

typedef struct ItemEntry {
    u8 pad_00[2];
    u16 order;
    s16 recordId;
    u8 pad_06[2];
    ItemInfo *info;
} ItemEntry;

typedef struct RecordEntry {
    u16 rank : 2;
    u16 grade : 3;
    u16 : 11;
    u16 active : 1;
    u16 level : 7;
} RecordEntry;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

int CompareItemEntries(ItemEntry **left, ItemEntry **right)
{
    ItemEntry *a = *left;
    ItemEntry *b = *right;
    RecordEntry *recordA;
    RecordEntry *recordB;
    int diff;

    diff = a->info->category - b->info->category;
    if (diff == 0) {
        diff = a->info->id - b->info->id;
        if (diff == 0 && (s16)(a->recordId | b->recordId) >= 0) {
            recordA = GetActiveRecordEntryOrNull((u16)a->recordId);
            recordB = GetActiveRecordEntryOrNull((u16)b->recordId);
            diff = recordA->rank - recordB->rank;
            if (diff == 0) {
                diff = recordA->level - recordB->level;
                if (diff == 0) {
                    diff = b->order - a->order;
                    if (diff == 0) {
                        diff = recordA->grade - recordB->grade;
                    }
                }
            }
        }
    }
    return diff;
}