#include "nitro/types.h"

typedef struct ActorModel {
    u32 flags;
    u8 animationState[0xfc];
    u16 animationSpeed;
} ActorModel;

typedef struct MotionData {
    u8 pad_00[0x84];
    u16 animationSpeed;
} MotionData;

typedef struct ActorMotion {
    u8 pad_00[4];
    MotionData *data;
    u8 pad_08[0xc4 - 0x08];
    s32 mode;
} ActorMotion;

typedef struct ActorEffect {
    u32 flags;
    u8 pad_04[4];
    u8 animationState[0x230 - 0x08];
} ActorEffect;

typedef struct Actor {
    u8 pad_000[0x230];
    ActorModel *model;
    u8 pad_234[0x274 - 0x234];
    ActorMotion motion;
    u8 pad_33c[0x9d4 - 0x33c];
    ActorEffect effects[2];
} Actor;

extern void Obj_SetHalfwordFC(void *animationState, u16 speed);
extern BOOL IsBit0Set(u32 *flags);

void Actor_SyncAnimationSpeed(Actor *actor)
{
    ActorMotion *motion = &actor->motion;
    u16 speed;
    int i;

    if (motion->mode != 2 || motion->data == NULL) {
        return;
    }
    speed = motion->data->animationSpeed;
    if (speed == 0) {
        if (actor->model->animationSpeed != 0) {
            return;
        }
        speed = 0x7fff;
    }
    Obj_SetHalfwordFC(actor->model->animationState, speed);
    for (i = 0; i < 2; i++) {
        if (IsBit0Set(&actor->effects[i].flags)) {
            Obj_SetHalfwordFC(actor->effects[i].animationState, speed);
        }
    }
}
