#include "nitro/types.h"

typedef struct ActorSlot {
    struct ActorSlot *next;
    struct ActorSlot *prev;
    u16 flags;
    u8 pad_0a[2];
    s8 depth;
    u8 pad_0d[7];
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
extern void InsertNodeByPriority(ActorSlot *slot, ActorSlot **head, ActorSlot **tail);
extern ActorRegistry *gActorRegistry;

void ActorSlot_AttachToParent(ActorSlot *child, ActorSlot *parent, void *initializationData)
{
    attach_child_object(child->node, parent->node, initializationData);
    child->flags |= 0xb;
    if (parent->flags & 0x20) {
        child->flags |= 0x20;
        if (child->depth < parent->depth) {
            child->depth = parent->depth + 1;
        }
        InsertNodeByPriority(child, &gActorRegistry->secondaryHead, &gActorRegistry->secondaryTail);
    } else {
        child->flags &= ~0x20;
        if (child->depth < parent->depth) {
            child->depth = parent->depth + 1;
        }
        InsertNodeByPriority(child, &gActorRegistry->primaryHead, &gActorRegistry->primaryTail);
    }
}
