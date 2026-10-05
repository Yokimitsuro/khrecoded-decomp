#include "nitro/types.h"
#include "nitro/fx_types.h"

struct TargetActor;

typedef struct ActorController {
    u8 pad_00[0x14];
    void (*getPosition)(struct TargetActor *actor, u16 pointId, VecFx32 *out);
} ActorController;

typedef struct TargetActor {
    u8 pad_000[0x278];
    ActorController *controller;
} TargetActor;

extern TargetActor *GetStageActor(s16 actorId);
extern void GetNodePosition(TargetActor *actor, u16 pointId, VecFx32 *out);

void GetTargetActorPointPosition(TargetActor *actor, u16 targetId, u16 pointId, VecFx32 *out)
{
    TargetActor *target;

    if (targetId == 0xffff) {
        if (actor->controller != NULL) {
            actor->controller->getPosition(actor, 0, out);
        }
    } else if (targetId != 0) {
        target = GetStageActor((s16)targetId);
        if (target != NULL) {
            GetNodePosition(target, pointId, out);
        }
    }
}
