#include "nitro/types.h"

typedef struct ActorGroupOwner {
    u8 pad_00[0x10];
    u16 groupId;
} ActorGroupOwner;

typedef struct StageActor {
    u8 pad_000[0x1d0];
    u8 component[1];
} StageActor;

extern StageActor *func_ov001_0209c068(s16 groupId);
extern void func_ov021_020b4bbc(void *component, void *arg);

void ForwardToGroupActorComponent(ActorGroupOwner *owner, void *arg)
{
    StageActor *actor;

    if (owner != NULL && owner->groupId != 0) {
        actor = func_ov001_0209c068(owner->groupId);
        if (actor != NULL) {
            func_ov021_020b4bbc(actor->component, arg);
        }
    }
}
