#include "nitro/types.h"

typedef struct ActorNode {
    u32 flags;
    u16 animFlags;
    u8 pad_006[0x7A];
    u16 animFrame;
} ActorNode;

typedef struct FieldObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x13];
    u16 resetFrame;
    u8 pad_4E[0xA];
    u8 state;
    u8 pad_59;
    s8 pendingIndex;
    u8 pad_5B[0x5];
    s32 frameTimer;
} FieldObject;

extern ActorNode *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void RebindAnimTracks(u16 *animFlags, s16 blend, int value);

void FieldObject_StopActorAnimation(FieldObject *object)
{
    ActorNode *actor;
    u16 frame;

    if (object->state != 3) {
        return;
    }
    actor = ActorRegistry_GetEntityByIndex(object->actorId);
    RebindAnimTracks(&actor->animFlags, 0, 0);
    object->frameTimer = object->resetFrame << 12;
    object->pendingIndex = -1;
    object->state = 0;
    frame = object->frameTimer >> 12;
    if (!(actor->flags & 0x20)) {
        actor->animFrame = frame;
        actor->animFlags |= 0x20;
    }
}
