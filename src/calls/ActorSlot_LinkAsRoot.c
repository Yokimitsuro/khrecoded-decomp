#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
} ActorSlot;

typedef struct {
    u8 pad_00[0x1c];
    ActorSlot *rootHead;
} ActorRegistry;

extern ActorRegistry *gActorRegistry;

void ActorSlot_LinkAsRoot(ActorSlot *slot)
{
    ActorRegistry *registry;
    ActorSlot *head;

    if (slot->flags & 2) {
        return;
    }
    slot->flags |= 0xa;
    registry = gActorRegistry;
    head = registry->rootHead;
    if (head != NULL) {
        slot->next = head;
        head->prev = slot;
    }
    registry->rootHead = slot;
}
