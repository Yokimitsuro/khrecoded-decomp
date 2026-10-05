#include "nitro/types.h"

typedef struct RecordEntry {
    u16 type : 2;
    u16 rank : 3;
    u16 unk_00_5 : 11;
    u16 active : 1;
    u16 level : 7;
    u16 unk_02_8 : 8;
} RecordEntry;

typedef struct ItemDef {
    int category;
    u8 pad_04[0x14];
    u16 sortKey;
} ItemDef;

typedef struct ItemSlot {
    u16 unk_00;
    u16 order;
    s16 recordIndex;
    u16 unk_06;
    ItemDef *def;
} ItemSlot;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

int CompareItemSlots(ItemSlot **left, ItemSlot **right)
{
    ItemSlot *a = *left;
    ItemSlot *b = *right;
    int diff;

    if ((diff = a->def->sortKey - b->def->sortKey) == 0 && (diff = a->def->category - b->def->category) == 0 &&
        (s16)(b->recordIndex | a->recordIndex) >= 0) {
        RecordEntry *entryA = GetActiveRecordEntryOrNull((u16)a->recordIndex);
        RecordEntry *entryB = GetActiveRecordEntryOrNull((u16)b->recordIndex);
        if ((diff = entryA->type - entryB->type) == 0 && (diff = entryA->level - entryB->level) == 0 &&
            (diff = b->order - a->order) == 0) {
            diff = entryA->rank - entryB->rank;
        }
    }
    return diff;
}