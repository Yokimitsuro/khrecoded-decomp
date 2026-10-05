#include "nitro/types.h"

extern void NNSi_FndFreeFromDefaultHeap(void *block);

typedef struct {
    u32 unused;
    void *data;
} EntryArraySlot;

typedef struct {
    u8 pad_00[0x84];
    s32 count;
    EntryArraySlot *entries;
} EntryArrayHolder;

void FreeEntryArray(EntryArrayHolder *holder)
{
    s32 i;

    if (holder->entries == 0) {
        return;
    }
    i = 0;
    if (0 < holder->count) {
        do {
            NNSi_FndFreeFromDefaultHeap(holder->entries[i].data);
            i = i + 1;
        } while (i < holder->count);
    }
    NNSi_FndFreeFromDefaultHeap(holder->entries);
    holder->entries = 0;
}
