#include "nitro/types.h"

typedef struct CacheEntry CacheEntry;

typedef struct CacheEntryOps {
    u8 pad_00[4];
    void (*onRelease)(CacheEntry *entry);
} CacheEntryOps;

struct CacheEntry {
    CacheEntry *next;
    CacheEntryOps *ops;
    u8 pad_08[0x2A];
    u8 actorIndex;
};

typedef struct CacheSlot {
    u32 key;
    void *block;
} CacheSlot;

typedef struct ResourceCache {
    u8 pad_000[5];
    u8 flags;
    u8 pad_006[2];
    CacheEntry *entries;
    u8 pad_00C[0x12C];
    CacheSlot slots[8];
} ResourceCache;

extern ResourceCache *data_ov001_020a04fc;
extern void *ActorSlot_GetByIndex(u32 actorIndex);
extern void *Obj_SetWord1C8(void *actor, void (*callback)(int, int));
extern void func_ov001_02086b14(int actor, int useCallback);
extern BOOL func_ov001_020645c8(u32 flagIndex);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ResourceCache_Shutdown(void)
{
    ResourceCache *cache = data_ov001_020a04fc;
    CacheEntry *entry;
    int i;

    for (entry = cache->entries; entry != NULL; entry = entry->next) {
        void *actor;

        if (entry->ops->onRelease != NULL) {
            entry->ops->onRelease(entry);
        }
        actor = ActorSlot_GetByIndex(entry->actorIndex);
        if (actor != NULL) {
            Obj_SetWord1C8(actor, func_ov001_02086b14);
        }
    }
    if (!func_ov001_020645c8(0x3614)) {
        for (i = 0; i < 8; i++) {
            if (cache->slots[i].block != NULL) {
                NNSi_FndFreeFromDefaultHeap(cache->slots[i].block);
                cache->slots[i].block = NULL;
            }
        }
    }
    cache->flags &= 0xF5;
}
