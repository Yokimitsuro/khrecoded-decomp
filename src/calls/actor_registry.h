#ifndef RECODED_ACTOR_REGISTRY_H
#define RECODED_ACTOR_REGISTRY_H

#include "nitro/types.h"

typedef struct ActorSlot {
    u8 pad_000[8];
    u16 flags;
    u8 modelExtra;
    u8 priority;
} ActorSlot;

typedef struct ActorSlotTail {
    u8 pad_100[0xc4];
    s16 field_1c4;
} ActorSlotTail;

typedef struct ActorRegistry {
    u8 pad_000[0x20];
    ActorSlot *slots[];
} ActorRegistry;

typedef struct ActorRegistryCollisionView {
    u8 pad_000[0x928];
    void *collisionResult;
} ActorRegistryCollisionView;

extern ActorRegistry *gActorRegistry;

#endif
