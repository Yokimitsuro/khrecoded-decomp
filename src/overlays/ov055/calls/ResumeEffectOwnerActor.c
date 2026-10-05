#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectSource {
    u8 pad_00[0x3d];
    s8 kind;
} EffectSource;

typedef struct EffectTask {
    u8 pad_00[0x50];
    EffectSource *source;
} EffectTask;

typedef struct EffectOwner {
    u8 pad_00[0x14];
    int player;
} EffectOwner;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onEvent)(Actor *actor, int event, int value);
    void (*onStop)(Actor *actor, int value);
    u8 pad_200[0x210 - 0x200];
    void (*setAngle)(Actor *actor, u16 angle);
    u8 pad_214[0x228 - 0x214];
    BOOL (*getTarget)(Actor *actor, VecFx32 *pos);
};

typedef void *(*StateHandler)(EffectOwner *owner, EffectTask *task, int *nextState);

extern Actor *GetBoundedEntryField(int index);
extern StateHandler SelectFallStateHandler(Actor *actor, int *nextState);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern unsigned short FX_Atan2Idx(int vertical, int horizontal);
extern void *UpdateEffectOwnerMotion(EffectOwner *owner, EffectTask *task, int *nextState);

void *ResumeEffectOwnerActor(EffectOwner *owner, EffectTask *task, int *nextState)
{
    Actor *actor = GetBoundedEntryField(owner->player);
    StateHandler handler = SelectFallStateHandler(actor, nextState);
    int event;
    BOOL found;
    VecFx32 target;
    VecFx32 diff;

    if (handler != NULL) {
        return handler;
    }
    switch (task->source->kind) {
    case 0:
        event = 0x1f;
        break;
    case 4:
        event = 0x21;
        break;
    }
    if (actor->onEvent != NULL) {
        actor->onEvent(actor, event, -1);
    }
    if (actor->onStop != NULL) {
        actor->onStop(actor, 0);
    }
    if (actor->getTarget == NULL) {
        found = FALSE;
    } else {
        found = actor->getTarget(actor, &target);
    }
    if (found) {
        VEC_Subtract(&target, func_ov052_020ceb74(actor), &diff);
        {
            u16 angle = FX_Atan2Idx(diff.x, diff.z) + 0x8000;
            if (actor->setAngle != NULL) {
                actor->setAngle(actor, angle);
            }
        }
    }
    *nextState = 0x1a;
    return UpdateEffectOwnerMotion;
}
