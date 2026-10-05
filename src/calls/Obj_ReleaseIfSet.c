#include "nitro/types.h"

typedef struct {
    u32 flags;
    void *resource;
    void *block;
} Entity;

extern u32 Obj_HasFlag0(void);
extern void *NNSi_FndGetAllocatorForDefaultHeap(u32 kind);
extern void NNS_FndFreeToAllocator(void *allocator, void *block);
extern void func_0202c8bc(void *resource);

void Obj_ReleaseIfSet(Entity *entity)
{
    if (Obj_HasFlag0() != 0) {
        NNS_FndFreeToAllocator(NNSi_FndGetAllocatorForDefaultHeap(0), entity->block);
        func_0202c8bc(entity->resource);
    }
    entity->flags = 0;
}
