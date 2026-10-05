#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Actor Actor;
typedef void (*ActorBlendCallback)(Actor *actor, fx32 weight);
typedef void (*ActorStateFunc)(Actor *actor, int state);

typedef struct AnimHolder {
    u32 pad_00;
    u8 player[1];
} AnimHolder;

struct Actor {
    u8 pad_0000[0x1fc];
    ActorBlendCallback onBlend;
    u8 pad_0200[0x230 - 0x200];
    AnimHolder *anim;
    u8 pad_0234[0x768 - 0x234];
    int pendingBlend;
    u8 pad_076c[0x928 - 0x76c];
    u64 statusFlags;
    u8 pad_0930[0x934 - 0x930];
    s32 mode : 8;
    s32 modeRest : 24;
    u8 subMode : 8;
    u8 pad_0939[0x948 - 0x939];
    fx32 chargeTime;
    u8 pad_094c[0x970 - 0x94c];
    VecFx32 moveVelocity;
    VecFx32 rootMotion;
    u8 pad_0988[0x1808 - 0x988];
    ActorStateFunc setState;
};

extern const VecFx32 data_0205344c;
extern fx32 func_0202f4cc(void *player, int arg);
extern void Actor_GetRootMotionDelta(Actor *actor, VecFx32 *out);
extern void SetClampedCursor(Actor *actor, int value);
extern void Actor_SetTimeScale(Actor *actor, fx32 scale);

void Actor_ResetMovementState(Actor *actor) {
    VecFx32 delta;

    actor->subMode = 0;
    actor->mode = 0;
    actor->moveVelocity = data_0205344c;
    Actor_GetRootMotionDelta(actor, &delta);
    actor->rootMotion = delta;
    if (actor->pendingBlend != 0) {
        fx32 frame = func_0202f4cc(actor->anim->player, 0) - FX32_ONE;
        if (actor->onBlend != NULL) {
            actor->onBlend(actor, frame);
        }
        actor->pendingBlend = 0;
    }
    if (actor->chargeTime >= 0x96000) {
        actor->statusFlags &= ~(u64)0x800;
        SetClampedCursor(actor, 999);
        Actor_SetTimeScale(actor, FX32_ONE);
        actor->setState(actor, 1);
    }
}
