#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct StageOwner {
    u8 pad_000[0x3b2];
    u16 linkedActorId;
} StageOwner;

extern StageActor *GetStageActor(int id);

StageActor *GetLinkedStageActor(StageOwner *owner)
{
    if (owner->linkedActorId == 0) {
        return NULL;
    }
    return GetStageActor((s16)owner->linkedActorId);
}
