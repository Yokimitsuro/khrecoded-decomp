#include "nitro/types.h"

typedef struct EffectEntry {
    u8 pad_00[0x34];
    void (*onDestroy)(struct EffectEntry *entry);
} EffectEntry;

typedef struct EffectList {
    EffectEntry **entries;
    s8 count;
} EffectList;

extern EffectList *data_ov001_020a04fc;

extern void DestroyEntryPool(EffectEntry *entry);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void DestroyAllEffectEntries(BOOL notify)
{
    EffectList *list = data_ov001_020a04fc;
    int i;
    EffectEntry *entry;

    for (i = 0; i < list->count; i++) {
        entry = list->entries[i];
        if (entry != NULL) {
            if (notify && entry->onDestroy != NULL) {
                entry->onDestroy(entry);
            }
            DestroyEntryPool(entry);
            list->entries[i] = NULL;
        }
    }
    list->count = 0;
    if (list->entries != NULL) {
        NNSi_FndFreeFromDefaultHeap(list->entries);
        list->entries = NULL;
    }
}
