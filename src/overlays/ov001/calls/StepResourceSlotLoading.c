#include "nitro/types.h"

typedef struct ResourceListener ResourceListener;

typedef struct ResourceListenerVtbl {
    void (*onLoaded)(ResourceListener *listener, int slot, void *record, void *file);
} ResourceListenerVtbl;

struct ResourceListener {
    ResourceListener *next;
    ResourceListenerVtbl *vtbl;
};

typedef struct ResourceEntry {
    s16 id;
    u8 flags;
    u8 pad_03;
    void *record;
    void *file;
} ResourceEntry;

typedef struct ResourceLoader {
    u8 pad_00[5];
    u8 flags;
    u8 pad_06[2];
    ResourceListener *listeners;
    u8 pad_0c[4];
    ResourceEntry *entries[1];
} ResourceLoader;

extern ResourceLoader *data_ov001_020a04fc;
extern const int data_ov001_0209e3c8[];
extern u32 ObjectManager_GetFirstEntryParam(int id);
extern u32 ObjectManager_GetSecondEntryParam(int id);
extern void *SND_RegisterSeq(u32 fileId, int flags);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

BOOL StepResourceSlotLoading(void)
{
    ResourceLoader *loader = data_ov001_020a04fc;
    int i;
    int slot;
    ResourceEntry *entry;
    ResourceListener *listener;

    if (loader->flags & 4) {
        for (i = 0; i < 21; i++) {
            slot = data_ov001_0209e3c8[i];
            entry = loader->entries[slot];
            if (entry == NULL || (entry->flags & 4)) {
                continue;
            }
            if (!(entry->flags & 1)) {
                entry->record = SND_RegisterSeq(ObjectManager_GetFirstEntryParam(entry->id), 4);
                entry->flags |= 1;
            }
            if (!(entry->flags & 2)) {
                entry->file = func_0202c4a0(ObjectManager_GetSecondEntryParam(entry->id), 4);
                entry->flags |= 2;
            }
            if (loader->flags & 8) {
                for (listener = loader->listeners; listener != NULL; listener = listener->next) {
                    listener->vtbl->onLoaded(listener, slot, entry->record, entry->file);
                }
                NNSi_FndFreeFromDefaultHeap(entry->file);
                entry->file = NULL;
                entry->flags |= 4;
                return FALSE;
            }
        }
    }
    loader->flags |= 4;
    return TRUE;
}
