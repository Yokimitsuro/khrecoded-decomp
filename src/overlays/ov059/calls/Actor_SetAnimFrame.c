#include "nitro/types.h"

typedef struct {
    u8 data[0x230];
} ModelSet;

typedef struct {
    u32 flags;
    u8 anim[4];
} BodyModel;

typedef struct {
    u8 pad_000[0x230];
    BodyModel *body;
    u8 pad_234[0x75c - 0x234];
    s32 motion;
    s32 frame;
    u8 pad_764[0x7f0 - 0x764];
    u8 stateMachine[0x998 - 0x7f0];
    u8 cueGroup[0x9d4 - 0x998];
    ModelSet modelSets[2];
} Actor;

extern int *func_01ffb2f8(void *anim, int channel, int frame);
extern void ApplyModelSetAnimations(ModelSet *set, int frame);
extern void func_ov021_020ac96c(void *stateMachine, int frame);
extern void func_ov021_020a8148(void *group, int motion, int frame);

void Actor_SetAnimFrame(Actor *actor, int frame)
{
    int i;

    func_01ffb2f8(actor->body->anim, 0, frame);
    for (i = 0; i < 2; i++) {
        ApplyModelSetAnimations(&actor->modelSets[i], frame);
    }
    actor->frame = frame;
    func_ov021_020ac96c(actor->stateMachine, frame);
    func_ov021_020a8148(actor->cueGroup, actor->motion, frame);
}
