#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorStepFunc)(Actor *actor, fx32 deltaTime);
typedef void (*ActorFunc)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1ec];
    ActorStepFunc step;
    u8 pad_01F0[0x940 - 0x1f0];
    ActorFunc stateUpdate;
    u8 pad_0944[0x958 - 0x944];
    fx32 timeScale;
    u8 pad_095C[0x1524 - 0x95c];
    u8 bufferSlots[0x180c - 0x1524];
    ActorFunc postUpdate;
};

extern void Actor_ApplyFrameMotion(void);
extern fx32 func_ov001_0206db44(void);
extern fx32 FX_Mul(fx32 left, fx32 right);
extern void func_ov059_020c7fac(Actor *actor);
extern void Actor_UpdateCommandInput(Actor *actor);
extern void func_ov059_020cfa18(void *bufferSlots, Actor *actor);

void Actor_Update(Actor *actor)
{
    fx32 deltaTime;

    Actor_ApplyFrameMotion();
    deltaTime = func_ov001_0206db44();
    deltaTime = FX_Mul(actor->timeScale, deltaTime);
    if (actor->step != NULL) {
        actor->step(actor, deltaTime);
    }
    func_ov059_020c7fac(actor);
    actor->stateUpdate(actor);
    Actor_UpdateCommandInput(actor);
    if (actor->postUpdate != NULL) {
        actor->postUpdate(actor);
    }
    func_ov059_020cfa18(actor->bufferSlots, actor);
}
