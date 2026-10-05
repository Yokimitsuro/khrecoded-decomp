#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *object;
    u8 pad_0c[4];
    void *buffer;
    u8 pad_14[0x18];
    int bufferId;
    u16 flags;
    u8 objectArg;
} PoolEntry;

typedef struct EntryPool {
    u8 pad_00[0x10];
    void (*onEntryDestroy)(PoolEntry *entry);
    void (*onPoolDestroy)(struct EntryPool *pool);
    u8 pad_18[0x26];
    u16 count;
} EntryPool;

extern PoolEntry *func_ov001_02086384(EntryPool *pool, int index);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void Obj_ConditionalShutdown(void *object, u16 arg);

void DestroyEntryPool(EntryPool *pool)
{
    u16 count = pool->count;
    PoolEntry *entry;
    int i;

    for (i = 0; i < count; i++) {
        entry = func_ov001_02086384(pool, i);
        if (entry->flags & 1) {
            if (pool->onEntryDestroy != NULL) {
                pool->onEntryDestroy(entry);
            }
            if (entry->bufferId != -1 && entry->buffer != NULL) {
                NNSi_FndFreeFromDefaultHeap(entry->buffer);
                entry->buffer = NULL;
            }
            if (entry->object != NULL) {
                Obj_ConditionalShutdown(entry->object, entry->objectArg);
                NNSi_FndFreeFromDefaultHeap(entry->object);
                entry->object = NULL;
            }
        }
    }
    if (pool->onPoolDestroy != NULL) {
        pool->onPoolDestroy(pool);
    }
    NNSi_FndFreeFromDefaultHeap(pool);
}
