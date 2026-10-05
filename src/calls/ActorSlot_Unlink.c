#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[6];
    u8 actor[4];
    u8 node[4];
} ActorSlot;

typedef struct {
    u8 pad_00[0xc];
    ActorSlot *secondaryHead;
    ActorSlot *secondaryTail;
    ActorSlot *primaryHead;
    ActorSlot *primaryTail;
} ActorRegistry;

extern void attach_child_object(void *child, void *parent, void *initializationData);
extern void Obj_RemoveFromQuadTree(void *entity);
extern ActorRegistry *data_0206083c;

static inline void RemoveFromList(ActorSlot *slot, ActorSlot **head, ActorSlot **tail)
{
    if (slot->next != NULL) {
        slot->next->prev = slot->prev;
    }
    if (slot->prev != NULL) {
        slot->prev->next = slot->next;
    }
    if (*head == slot) {
        *head = slot->next;
    }
    if (*tail == slot) {
        *tail = slot->prev;
    }
    slot->prev = NULL;
    slot->next = NULL;
}

void ActorSlot_Unlink(ActorSlot *slot)
{
    if ((slot->flags & 2) == 0) {
        return;
    }
    if (slot->flags & 4) {
        attach_child_object(slot->node, NULL, NULL);
    }
    Obj_RemoveFromQuadTree(slot->actor);
    if (slot->flags & 0x20) {
        RemoveFromList(slot, &data_0206083c->secondaryHead, &data_0206083c->secondaryTail);
    } else {
        RemoveFromList(slot, &data_0206083c->primaryHead, &data_0206083c->primaryTail);
    }
    slot->flags &= 0xfef5;
}
