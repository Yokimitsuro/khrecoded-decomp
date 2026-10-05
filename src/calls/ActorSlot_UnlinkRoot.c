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

extern ActorRegistry *data_0206083c;

void ActorSlot_UnlinkRoot(ActorSlot *slot)
{
    ActorRegistry *registry;

    if ((slot->flags & 2) == 0) {
        return;
    }
    slot->flags &= 0xfff5;
    registry = data_0206083c;
    if (slot->next != NULL) {
        slot->next->prev = slot->prev;
    }
    if (slot->prev != NULL) {
        slot->prev->next = slot->next;
    }
    if (registry->rootHead == slot) {
        registry->rootHead = slot->next;
    }
    slot->prev = NULL;
    slot->next = NULL;
}
