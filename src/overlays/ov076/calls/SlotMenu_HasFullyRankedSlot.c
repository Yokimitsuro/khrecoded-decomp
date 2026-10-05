#include "nitro/types.h"

typedef struct RecordEntry {
    u16 kind : 2;
    u16 rank : 3;
    u16 levelProgress : 11;
} RecordEntry;

typedef struct SlotPair {
    u16 first;
    u16 second;
} SlotPair;

typedef struct SaveData {
    u8 pad_0000[0x2c68];
    u8 extraSlotCount;
    u8 pad_2C69[0x2d84 - 0x2c69];
    SlotPair slotPairs[8];
} SaveData;

extern SaveData *data_0205fe0c;
extern RecordEntry *GetActiveRecordEntryOrNull(u16 index);

static inline BOOL IsHandleValid(u32 handle)
{
    BOOL valid = FALSE;
    if (handle >= 0x200 && handle < 0x458) {
        valid = TRUE;
    }
    return valid;
}

BOOL SlotMenu_HasFullyRankedSlot(void)
{
    int slot;
    int slotCount = data_0205fe0c->extraSlotCount + 3;

    for (slot = 0; slot < slotCount; slot++) {
        BOOL ranked = FALSE;
        u16 first = data_0205fe0c->slotPairs[slot].first;
        u16 second = data_0205fe0c->slotPairs[slot].second;
        if (IsHandleValid(first) && GetActiveRecordEntryOrNull(first - 0x200)->rank != 0) {
            ranked = TRUE;
        }
        if (ranked) {
            ranked = FALSE;
            if (IsHandleValid(second) && GetActiveRecordEntryOrNull(second - 0x200)->rank != 0) {
                ranked = TRUE;
            }
            if (ranked) {
                return TRUE;
            }
        }
    }
    return FALSE;
}