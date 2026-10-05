#include "nitro/types.h"

typedef struct CacheSlot {
    u32 key;
    void *block;
} CacheSlot;

typedef struct ResourceCache {
    u8 pad_000[0x138];
    CacheSlot slots[8];
    u8 extraSlots[0x40];
} ResourceCache;

extern ResourceCache *data_ov001_020a04fc;
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MIi_CpuClear32(u32 value, void *destination, u32 size);

void ResourceCache_FreeAll(void)
{
    int i;
    ResourceCache *cache = data_ov001_020a04fc;

    for (i = 0; i < 8; i++) {
        if (cache->slots[i].block != NULL) {
            NNSi_FndFreeFromDefaultHeap(cache->slots[i].block);
        }
    }
    MIi_CpuClear32(0, cache->slots, sizeof(cache->slots));
    MIi_CpuClear32(0, cache->extraSlots, sizeof(cache->extraSlots));
}
