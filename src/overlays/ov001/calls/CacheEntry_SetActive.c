#include "nitro/types.h"

typedef struct RegisteredActor {
    u8 pad_00[8];
    u16 flags;
} RegisteredActor;

typedef struct CacheEntry CacheEntry;

typedef struct CacheEntryOps {
    u8 pad_00[0x18];
    void (*onSetActive)(CacheEntry *entry, BOOL active);
} CacheEntryOps;

struct CacheEntry {
    u8 pad_00[4];
    CacheEntryOps *ops;
    RegisteredActor *actor;
    u8 pad_0C[0x24];
    u16 flags;
    u8 bitIndex;
};

typedef struct ResourceCache {
    u8 pad_000[0x178];
    u32 inactiveBits[0x10];
} ResourceCache;

extern ResourceCache *data_ov001_020a04fc;
extern void WritePackedBits(u32 *base, u32 bitOffset, u32 bitCount, u32 value);
extern void ActorSlot_AddToWorld(RegisteredActor *actor);
extern void func_020369a8(RegisteredActor *actor);

void CacheEntry_SetActive(CacheEntry *entry, BOOL active)
{
    WritePackedBits(data_ov001_020a04fc->inactiveBits, entry->bitIndex, 1, active == FALSE);
    if (entry->flags & 4) {
        if (active) {
            if (!(entry->actor->flags & 0x100)) {
                ActorSlot_AddToWorld(entry->actor);
            }
        } else {
            if (entry->actor->flags & 0x100) {
                func_020369a8(entry->actor);
            }
        }
    }
    if (entry->ops->onSetActive != NULL) {
        entry->ops->onSetActive(entry, active);
    }
}
