#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[6];
    u8 entity[4];
} ActorSlot;

typedef struct {
    u16 unk_00;
    u16 recordCount;
    void **records;
    void *buffer;
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
    ActorSlot *rootHead;
    ActorSlot *slots[0x200];
} ActorRegistry;

extern void ApplyRecordTableEntry3(u16 index);
extern void ActorSlot_UnlinkByIndex(u16 index);
extern void Obj_ShutdownBase(void *entity);
extern void FreeRecordArrayAndReset(ActorRegistry *registry);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern ActorRegistry *data_0206083c;

void ShutdownAllActorSlots(void)
{
    ActorRegistry *registry = data_0206083c;
    int i;

    for (i = 0; i < 0x200; i++) {
        ActorSlot *slot = registry->slots[i];
        if (slot != NULL && (slot->flags & 4) && (slot->flags & 2) && (slot->flags & 0x40) == 0) {
            ApplyRecordTableEntry3(i);
            if (slot->flags & 2) {
                ActorSlot_UnlinkByIndex(i);
            }
            Obj_ShutdownBase(data_0206083c->slots[i]->entity);
            slot->flags = 0;
            registry->slots[i] = NULL;
        }
    }
    FreeRecordArrayAndReset(registry);
    if (registry->buffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(registry->buffer);
        registry->buffer = NULL;
    }
    registry->secondaryHead = NULL;
    registry->primaryHead = NULL;
    registry->rootHead = NULL;
    registry->secondaryTail = NULL;
    registry->primaryTail = NULL;
}
