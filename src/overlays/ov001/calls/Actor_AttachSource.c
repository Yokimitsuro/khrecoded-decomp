#include "nitro/types.h"

typedef struct SourceData {
    u8 pad_00[0x80];
    u16 heading;
} SourceData;

typedef struct ActorSource {
    SourceData *data;
} ActorSource;

typedef struct Actor {
    u8 pad_000[0xd18];
    ActorSource *source;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
    s32 targetAngle;
    s32 angle;
} Actor;

extern void ActorObject_Reset(Actor *actor, int mode);

void Actor_AttachSource(Actor *actor, int mode, ActorSource *source)
{
    s32 heading;

    if (actor->flags != 0) {
        return;
    }
    ActorObject_Reset(actor, mode);
    if (source == NULL) {
        actor->flags |= 0x4000;
        actor->source = NULL;
        return;
    }
    actor->flags |= 0x8000;
    actor->source = source;
    heading = source->data->heading;
    actor->angle = heading;
    actor->targetAngle = heading;
}
