#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x14];
    char name[1];
} AnimationResource;

typedef struct {
    u8 pad_00[0x74];
    AnimationResource *resource;
    u8 pad_78[0x60];
    u8 blendTable[0x2c];
} ActorAnimation;

typedef struct {
    u8 pad[0x370];
    ActorAnimation animation;
} AnimatedActor;

typedef struct {
    u8 pad_000[0x86c];
    fx32 blendSpeed;
    u8 pad_870[0x24];
    AnimatedActor body;
    u8 pad_body_end[0xd14 - 0x894 - sizeof(AnimatedActor)];
    int loopMode;
    u8 pad_d18[0xef4 - 0xd18];
    u32 flags;
} ActorController;

extern int strcmp(const char *a, const char *b);
extern void selectJointAnimationBlend(void *anim, u16 trackIndex, void *blendTable, short blendIndex);
extern void BindActorAnimation(AnimatedActor *actor, const char *name, int blendIndex);

void PlayActorAnimationByName(ActorController *controller, const char *name, int blendIndex, int loopMode)
{
    AnimatedActor *body = &controller->body;

    if (body->animation.resource != NULL && strcmp(body->animation.resource->name, name) == 0) {
        selectJointAnimationBlend(&body->animation, 0, body->animation.blendTable, blendIndex);
    } else {
        BindActorAnimation(body, name, blendIndex);
        controller->blendSpeed = 0x1000;
    }
    controller->loopMode = loopMode;
    controller->flags |= 0x40;
}
