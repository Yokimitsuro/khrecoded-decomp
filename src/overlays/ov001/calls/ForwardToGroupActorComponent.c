#include "nitro/types.h"

typedef struct ActorGroupOwner {
    u8 pad_00[0x10];
    u16 groupId;
} ActorGroupOwner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 component[1];
} StageActor;

extern StageActor *GetStageActor(s16 groupId);
extern void RunOverrideTrack(void *component, void *arg);

void ForwardToGroupActorComponent(ActorGroupOwner *owner, void *arg)
{
    StageActor *actor;

    if (owner != NULL && owner->groupId != 0) {
        actor = GetStageActor(owner->groupId);
        if (actor != NULL) {
            RunOverrideTrack(actor->component, arg);
        }
    }
}
