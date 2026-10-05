#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Actor Actor;
typedef void (*ActorBlendCallback)(Actor *actor, fx32 weight);

typedef struct AnimHolder {
    u32 pad_00;
    u8 player[1];
} AnimHolder;

struct Actor {
    u8 pad_000[0x1fc];
    ActorBlendCallback onBlend;
    u8 pad_200[0x230 - 0x200];
    AnimHolder *anim;
    u8 pad_234[0x75c - 0x234];
    int animId;
    u8 pad_760[0x768 - 0x760];
    int pendingBlend;
    u8 pad_76c[0x7f0 - 0x76c];
    u8 selector[0x93c - 0x7f0];
    int state;
};

extern int GetStateTransitionDelay(u32 next, u32 current, int state);
extern void SelectAnimationById(void *selector, int id);
extern fx32 func_0202f4cc(void *player, int arg);
extern void Actor_PlayAnimation(Actor *actor, void *table, int trackIndex, int blendIndex, int frameCount);
extern void EffectSlot_StartByKind(Actor *owner, int slotIndex, int kind, int arg);

void Actor_ChangeAnimation(Actor *actor, void *table, int animId, int blendIndex, int frameCount) {
    int current = actor->animId;
    int frames = frameCount;
    int i;

    if (frames < 0) {
        frames = GetStateTransitionDelay(animId, current, actor->state);
    }
    SelectAnimationById(actor->selector, animId);
    if (frames > 0 && actor->pendingBlend != 0) {
        fx32 frame = func_0202f4cc(actor->anim->player, 0) - FX32_ONE;
        if (actor->onBlend != NULL) {
            actor->onBlend(actor, frame);
        }
    }
    Actor_PlayAnimation(actor, table, 0, blendIndex, frames);
    for (i = 0; i < 2; i++) {
        EffectSlot_StartByKind(actor, i, animId, frames);
    }
    if (actor->onBlend != NULL) {
        actor->onBlend(actor, 0);
    }
    actor->animId = animId;
    actor->pendingBlend = 0;
}
