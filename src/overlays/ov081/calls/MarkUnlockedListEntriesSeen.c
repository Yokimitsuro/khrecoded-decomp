#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x6348];
    u8 *bitIndexTable;
} Ov081State;

typedef struct EntryList {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

extern Ov081State *data_ov081_020c5da0;
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern u16 *func_ov081_020c5c04(int id);
extern EntryList *func_ov081_020c544c(Ov081State *state);

static inline BOOL IsListEntryUnlocked(u8 id)
{
    u16 *entry;
    BOOL ok;

    if (IsGlobalPackedBitSet(data_ov081_020c5da0->bitIndexTable[id - 2] + 0xf50)
        && (entry = func_ov081_020c5c04(id)) != NULL
        && !(*entry == 0x30 && *entry == 0x2e && *entry == 0x30)
        && !(*entry == 0x2f && *entry == 0x2f)) {
        ok = TRUE;
    } else {
        ok = FALSE;
    }
    return ok;
}

void MarkUnlockedListEntriesSeen(Ov081State *state)
{
    EntryList *list;
    int i;
    u8 id;

    list = func_ov081_020c544c(state);
    if (list->kind == 1) {
        for (i = 0; i < list->count; i++) {
            id = list->ids[i];
            if (IsListEntryUnlocked(id)) {
                SetGlobalPackedBit(data_ov081_020c5da0->bitIndexTable[id - 2] + 0x1010);
            }
        }
    } else {
        id = list->count;
        if (IsListEntryUnlocked(id)) {
            SetGlobalPackedBit(data_ov081_020c5da0->bitIndexTable[id - 2] + 0x1010);
        }
    }
}
