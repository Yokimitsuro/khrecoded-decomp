#include "nitro/types.h"

typedef struct EntryList {
    u8 kind;
    u8 count;
    u8 pad_02[2];
    u8 *ids;
} EntryList;

typedef struct Ov081State {
    u8 pad_00[0x6120];
    EntryList *entries[110];
    u8 visibleIndices[110];
    u8 pad_6346[2];
    u8 *bitIndexTable;
    u8 unseen[110];
    u8 unseenIcons[9];
    u8 visibleCount;
    u8 shownCount;
    u8 unseenIconCount;
} Ov081State;

extern Ov081State *data_ov081_020c5da0;
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern u16 *func_ov081_020c5c04(int id);
extern void *func_ov039_020bc1ec(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern u8 PXI_Init_0204f0c8(void *container, int a, int b);

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

static inline BOOL IsListEntrySeen(u8 id)
{
    return IsGlobalPackedBitSet(data_ov081_020c5da0->bitIndexTable[id - 2] + 0x1010);
}

void BuildVisibleEntryIndex(Ov081State *state)
{
    void *container;
    int i;
    BOOL visible;
    int next;
    EntryList *list;
    u8 id;
    int j;
    int count;
    int k;

    container = func_ov039_020bc1ec();
    MI_CpuFill8(state->unseen, 0, sizeof(state->unseen));
    MI_CpuFill8(state->unseenIcons, 0xff, sizeof(state->unseenIcons));
    state->visibleCount = 0;
    state->unseenIconCount = 0;
    for (i = 0; i < 110; i++) {
        visible = FALSE;
        list = state->entries[i];
        switch (list->kind) {
        case 0:
            id = list->count;
            if (IsListEntryUnlocked(id)) {
                visible = TRUE;
                if (!IsListEntrySeen(id)) {
                    state->unseen[state->visibleCount] = visible;
                }
            }
            break;
        case 1:
            for (j = 0; j < list->count; j++) {
                id = list->ids[j];
                if (IsListEntryUnlocked(id)) {
                    visible = TRUE;
                    if (!IsListEntrySeen(id)) {
                        state->unseen[state->visibleCount] = TRUE;
                        break;
                    }
                }
            }
            break;
        case 2:
            for (next = i + 1; next < 110; next++) {
                list = state->entries[next];
                switch (list->kind) {
                case 0:
                    if (IsListEntryUnlocked(list->count)) {
                        visible = TRUE;
                        goto done;
                    }
                    break;
                case 1:
                    for (k = 0; k < list->count; k++) {
                        if (IsListEntryUnlocked(list->ids[k])) {
                            visible = TRUE;
                            goto done;
                        }
                    }
                    break;
                case 2:
                    visible = FALSE;
                    goto done;
                }
            }
        done:
            break;
        }
        if (visible) {
            if (state->unseen[state->visibleCount] != 0 && state->unseenIconCount < 9) {
                state->unseenIcons[state->unseenIconCount++] = PXI_Init_0204f0c8(container, 0, 1);
            }
            state->visibleIndices[state->visibleCount++] = i;
        }
    }
    count = state->visibleCount;
    if (count > 9) {
        count = 9;
    }
    state->shownCount = count;
}
