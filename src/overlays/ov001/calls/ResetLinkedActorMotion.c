#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct ActorLink {
    u8 pad_00[0x10];
    s16 actorId;
} ActorLink;

extern StageActor *func_ov001_0209c068(int id);
extern void func_ov001_02091ae8(StageActor *actor, int first, int second, int flags);

void ResetLinkedActorMotion(ActorLink *link)
{
    StageActor *actor = func_ov001_0209c068(link->actorId);

    if (actor != NULL) {
        func_ov001_02091ae8(actor, 0xffff, 0xffff, 0);
    }
}
