#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xd8];
    u8 blendTarget[0x34];
    int animId;
    int frame;
    int playing;
} AnimState;

typedef struct {
    u8 pad_000[0x3a4];
    AnimState *anim;
} AnimActor;

extern int GetActorAnimTrack(AnimActor *actor, u8 animId);
extern void selectJointAnimationBlend(void *state, int joint, void *target, s16 track);
extern void func_01ffb2f8(void *state, int a, int b);

void PlayActorAnimation(AnimActor *actor, int animId) {
    AnimState *anim = actor->anim;

    if (anim != NULL) {
        int track = GetActorAnimTrack(actor, animId);
        if (track >= 0) {
            anim->playing = 1;
            anim->frame = 0;
            anim->animId = animId;
            selectJointAnimationBlend(anim, 0, anim->blendTarget, track);
            func_01ffb2f8(anim, 0, 0);
        } else {
            anim->playing = 0;
            anim->animId = -1;
        }
    }
}
