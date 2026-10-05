#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorPlayFunc)(Actor *actor, int anim, int arg);
typedef void (*ActorBlendFunc)(Actor *actor, fx32 weight);

struct Actor {
    u8 pad_000[0x1f8];
    ActorPlayFunc play;
    ActorBlendFunc onBlend;
    u8 pad_200[0x94c - 0x200];
    VecFx32 knockback;
};

extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern int FX_Atan2Idx(fx32 y, fx32 x);
extern u32 func_0202a9e4(int range);

void Actor_PlayHitReaction(Actor *actor) {
    u16 facing = GetLinkedAngleOffset_020cd104(actor);
    VecFx32 dir;
    u16 angle;
    int diff;
    int anim;

    dir = actor->knockback;
    dir.y = 0;
    if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
        VEC_Normalize(&dir, &dir);
        angle = FX_Atan2Idx(-dir.x, -dir.z);
    } else {
        angle = facing - 0x8000;
    }
    diff = (u16)(angle - facing);
    if (diff > 0x8000) {
        diff = (u16)(0x10000 - diff);
    }
    {
        u32 roll = func_0202a9e4(2);
        if (diff > 0x4000) {
            anim = (roll & 1) ? 5 : 6;
        } else {
            anim = (roll & 1) ? 7 : 8;
        }
    }
    if (actor->play != NULL) {
        actor->play(actor, anim, -1);
    }
    if (actor->onBlend != NULL) {
        actor->onBlend(actor, 0);
    }
}
