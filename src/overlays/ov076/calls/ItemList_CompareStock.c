#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 variant : 3;
    u16 levelProgress : 11;
    u16 active : 1;
    u16 level : 7;
    u16 category : 8;
} RecordEntry;

typedef struct ItemDef {
    u32 handle;
    u8 pad_04[0x14];
    u16 sortKey;
} ItemDef;

typedef struct ItemStock {
    u16 total;
    u16 used;
    s16 recordIndex;
    u8 pad_06[2];
    ItemDef *def;
} ItemStock;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

int ItemList_CompareStock(ItemStock **left, ItemStock **right)
{
    ItemStock *a = *left;
    ItemStock *b = *right;
    int diff;

    diff = a->def->sortKey - b->def->sortKey;
    if (diff == 0) {
        diff = a->def->handle - b->def->handle;
        if (diff == 0 && (s16)(b->recordIndex | a->recordIndex) >= 0) {
            RecordEntry *recordA = GetActiveRecordEntryOrNull((u16)a->recordIndex);
            RecordEntry *recordB = GetActiveRecordEntryOrNull((u16)b->recordIndex);

            diff = recordA->kind - recordB->kind;
            if (diff == 0) {
                diff = recordA->level - recordB->level;
                if (diff == 0) {
                    diff = b->used - a->used;
                    if (diff == 0) {
                        diff = recordA->variant - recordB->variant;
                    }
                }
            }
        }
    }
    return diff;
}
