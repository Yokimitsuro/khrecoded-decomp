#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorAnimation {
    u8 pad0[0x20];
    u32 flags;
    u8 pad24[0x30];
    void *owner;
    u8 pad58[0x1c];
    void *resource;
    u8 pad78[0x60];
    u8 blendTable[0x2c];
    VecFx32 offset;
} ActorAnimation;

typedef struct AnimatedActor {
    u8 pad[0x370];
    ActorAnimation animation;
} AnimatedActor;

extern const VecFx32 data_0205344c;
extern void ReleaseResourceAndDetach(void *object);
extern void InitSharedRecordAndDispatchZero(void *dst, int a, void *info, int b);
extern void selectJointAnimationBlend(void *anim, u16 trackIndex, void *blendTable, short blendIndex);

void BindActorAnimation(AnimatedActor *actor, int animationId, int blendIndex) {
    if (actor->animation.resource != NULL) {
        ReleaseResourceAndDetach(&actor->animation);
    }
    InitSharedRecordAndDispatchZero(&actor->animation, animationId, NULL, 0xd);
    selectJointAnimationBlend(&actor->animation, 0, actor->animation.blendTable, blendIndex);
    actor->animation.owner = actor;
    actor->animation.flags |= 2;
    actor->animation.offset = data_0205344c;
}
