#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorBody {
    void *anim;
    u32 flags;
    VecFx32 velocity;
    u8 pad_14[0x2c - 0x14];
    fx32 fallSpeed;
} ActorBody;

typedef struct Actor {
    u8 pad_0000[0x230];
    ActorBody body;
    u8 pad_0260[0x928 - 0x260];
    u64 statusFlags;
    u8 pad_0930[0x970 - 0x930];
    VecFx32 moveVelocity;
    VecFx32 rootMotion;
} Actor;

extern const VecFx32 data_0205344c;
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void Actor_ConsumeKnockback(Actor *actor, VecFx32 *out);
extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern void func_ov059_020c8580(Actor *actor, VecFx32 *motion);
extern void func_02038e80(ActorBody *body, int arg);
extern void func_ov059_020c8a2c(Actor *actor);

void Actor_ApplyFrameMotion(Actor *actor) {
    VecFx32 motion;
    VecFx32 push;
    VecFx32 delta;
    BOOL apply;
    ActorBody *body;

    VEC_Add(&actor->rootMotion, &actor->moveVelocity, &delta);
    motion = delta;
    actor->rootMotion = data_0205344c;
    if (!(actor->statusFlags & 0x20) && !(actor->statusFlags & 0x800)) {
        Actor_ConsumeKnockback(actor, &push);
        if (push.x != 0 || push.y != 0 || push.z != 0) {
            VEC_Add(&motion, &push, &motion);
        }
    }
    apply = FALSE;
    if (actor->body.fallSpeed != (fx32)0x80000000) {
        apply = TRUE;
    } else if (motion.y != 0 || !(actor->body.flags & 4)) {
        apply = TRUE;
    }
    if (apply) {
        actor->body.fallSpeed = motion.y;
    }
    if (Actor_GetModelPosition(actor)->y < 0) {
        func_ov059_020c8580(actor, &motion);
    }
    body = &actor->body;
    body->velocity.x = motion.x;
    body->velocity.y = 0;
    body->velocity.z = motion.z;
    if (!(actor->statusFlags & 1)) {
        func_02038e80(body, 1);
    }
    actor->statusFlags &= ~(u64)1;
    func_ov059_020c8a2c(actor);
}
