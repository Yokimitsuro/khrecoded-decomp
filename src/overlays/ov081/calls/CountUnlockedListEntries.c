#include "nitro/types.h"

typedef struct Ov081State {
    u8 pad_00[0x6348];
    u8 *bitIndexTable;
    u8 pad_634c[0x7a];
    s8 cursor;
} Ov081State;

typedef struct EntryList {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

extern Ov081State *data_ov081_020c5da0;
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern u16 *func_ov081_020c5c04(int id);

void CountUnlockedListEntries(Ov081State *state, EntryList *list, int *total, int *before)
{
    int i;
    u8 id;
    u16 *entry;
    BOOL ok;

    if (list->kind == 1) {
        *total = 0;
        *before = -1;
        for (i = 0; i < list->count; i++) {
            id = list->ids[i];
            if (IsGlobalPackedBitSet(data_ov081_020c5da0->bitIndexTable[id - 2] + 0xf50)
                && (entry = func_ov081_020c5c04(id)) != NULL
                && !(*entry == 0x30 && *entry == 0x2e && *entry == 0x30)
                && !(*entry == 0x2f && *entry == 0x2f)) {
                ok = TRUE;
            } else {
                ok = FALSE;
            }
            if (ok) {
                (*total)++;
                if (i <= state->cursor) {
                    (*before)++;
                }
            }
        }
    } else {
        *before = 0;
        *total = 1;
    }
}
