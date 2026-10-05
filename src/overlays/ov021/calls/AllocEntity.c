#include "nitro/types.h"

typedef struct {
    u8 header[0x3c];
    u8 kind;
    u8 ownerId;
    u8 unk_3E;
    u8 unk_3F;
    u8 unk_40;
    u8 pad_41[0x107];
    u32 unk_148;
    u8 pad_14C[0x28];
    u32 unk_174;
    u8 pad_178[0x10];
    u16 entityId;
} Entity;

extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void InitObjWithCallback(void *obj, u32 arg1, u32 arg2);

Entity *AllocEntity(u8 ownerId, u16 entityId, u32 size, u32 kind)
{
    Entity *entity = NNSi_FndAllocFromDefaultHeap(size);

    entity->ownerId = ownerId;
    entity->unk_3F = 0;
    entity->entityId = entityId;
    entity->unk_40 = 0;
    entity->kind = kind;
    entity->unk_174 = 0;
    entity->unk_148 = 0;
    InitObjWithCallback(entity, kind, 1);
    return entity;
}
