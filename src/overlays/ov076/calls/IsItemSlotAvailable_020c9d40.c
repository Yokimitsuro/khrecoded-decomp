#include "nitro/types.h"

typedef struct {
    u16 flags : 2;
    u16 level : 3;
} RecordEntry;

typedef struct {
    u8 pad_00[4];
    u32 id;
} ItemDef;

typedef struct {
    u16 total;
    u16 used;
    s16 recordIndex;
    u16 pad_06;
    ItemDef *def;
} ItemSlot;

extern RecordEntry *GetActiveRecordEntryOrNull(int index);

BOOL IsItemSlotAvailable_020c9d40(ItemSlot *slot, u32 count, u32 *ids) {
    u32 i;
    u32 id;
    s16 recordIndex;
    if (count != 0) {
        id = slot->def->id;
        recordIndex = slot->recordIndex;
        if (recordIndex >= 0 || slot->total - slot->used > 0) {
            for (i = 0; i < count; i++) {
                if (id == ids[i]) {
                    if (recordIndex >= 0) {
                        if (slot->used == 0) {
                            return TRUE;
                        }
                    } else {
                        return TRUE;
                    }
                }
            }
        }
    } else {
        BOOL result = FALSE;
        BOOL available = FALSE;
        if (slot->recordIndex >= 0 && slot->used == 0) {
            available = TRUE;
        }
        if (available && GetActiveRecordEntryOrNull((u16)slot->recordIndex)->level != 0) {
            result = TRUE;
        }
        return result;
    }
    return FALSE;
}
