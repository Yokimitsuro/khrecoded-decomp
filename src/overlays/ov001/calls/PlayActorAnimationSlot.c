#include "nitro/types.h"

typedef struct {
    u32 unk0;
    u8 fade[0x74];
    void *model;
} ActorRender;

typedef struct {
    u8 pad_000[0x10];
    ActorRender render;
    u8 pad_08c[0x282 - 0x8c];
    u8 loopMask;
    u8 pendingMask;
    u8 pad_284[0x28a - 0x284];
    u16 unk28a_0 : 14;
    u16 hasAnimations : 1;
    u16 unk28a_15 : 1;
    u8 pad_28c[0x2e4 - 0x28c];
    u8 currentAnim;
} StageActor;

extern BOOL func_ov001_020919b8(StageActor *actor, u32 resourceIndex);
extern void BlendToAnimationTrack(void *state, int trackIndex, void *table, int blendIndex, int frameCount);

void PlayActorAnimationSlot(StageActor *actor, int slot, u32 anim, int frames, BOOL loop) {
    ActorRender *render = &actor->render;
    int bit;

    if (anim == 0xff) {
        return;
    }
    bit = 1 << slot;
    actor->loopMask &= (u8)~bit;
    actor->pendingMask &= (u8)~bit;
    if (loop) {
        actor->loopMask |= (u8)bit;
    }
    if (render->model == NULL) {
        return;
    }
    if (slot == 0) {
        if (actor->hasAnimations == 1) {
            if (actor->currentAnim == anim) {
                return;
            }
            if (!func_ov001_020919b8(actor, anim)) {
                return;
            }
            BlendToAnimationTrack(render->fade, slot, NULL, 0, 0);
            actor->currentAnim = anim;
            return;
        }
        actor->currentAnim = anim;
    }
    BlendToAnimationTrack(render->fade, slot, NULL, anim, frames);
}
