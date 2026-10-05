#include "nitro/types.h"

typedef struct Actor {
    void *owner;
    u8 pad_004[0xEF0];
    u32 flags;
    u8 pad_ef8[8];
    u32 kind;
    u32 childCount;
} Actor;

extern void Actor_InstallModelCallback(Actor *actor);

void AttachActorToOwner(Actor *newActor, Actor *owner, u32 kind)
{
    newActor->flags = 0x29;
    newActor->kind = kind;
    owner->childCount = owner->childCount + 1;
    if ((owner->flags & 0x400) == 0) {
        Actor_InstallModelCallback(owner);
    }
    newActor->owner = owner;
}
