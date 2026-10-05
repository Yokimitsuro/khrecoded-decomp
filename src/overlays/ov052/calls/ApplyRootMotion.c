#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionActor MotionActor;
typedef void (*ActorEventFunc)(MotionActor *actor, int event);

struct MotionActor {
    u8 pad_000[0x768];
    int eventFlag;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 pad_9b4[0x9c4 - 0x9b4];
    fx32 speed;
    VecFx32 velocity;
    u8 pad_9d4[0x10ec - 0x9d4];
    ActorEventFunc onEvent;
};

extern BOOL TryStartSpecialAction(MotionActor *actor);
extern void ComputeRootMotionDelta(MotionActor *actor, VecFx32 *delta);
extern VecFx32 *func_ov052_020ceb74(MotionActor *actor);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov052_020ceb80(MotionActor *actor, VecFx32 *position);

void ApplyRootMotion(MotionActor *actor)
{
    VecFx32 delta;
    VecFx32 position;

    if (actor->speed >= 0xf000 && TryStartSpecialAction(actor)) {
        return;
    }
    if (actor->eventFlag != 0) {
        actor->onEvent(actor, 4);
        return;
    }
    ComputeRootMotionDelta(actor, &delta);
    if (actor->speed >= 0x5000) {
        if (delta.y != 0) {
            actor->velocity.y = delta.y;
        }
        actor->velocity.x += delta.x;
        actor->velocity.z += delta.z;
        return;
    }
    actor->stateFlags |= 1;
    VEC_Add(func_ov052_020ceb74(actor), &delta, &position);
    func_ov052_020ceb80(actor, &position);
}
