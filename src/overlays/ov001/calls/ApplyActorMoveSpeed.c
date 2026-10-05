#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MovingActor {
    u8 pad_000[0x26c];
    u32 behaviorFlags : 31;
    u32 unk_26C_31 : 1;
    u8 pad_270[0x18];
    u16 unk_288_0 : 11;
    u16 overshootTarget : 1;
    u16 unk_288_12 : 1;
    u16 ignoreStopDistance : 1;
    u16 unk_288_14 : 2;
    u16 unk_28A_0 : 2;
    u16 snapMode : 3;
    u16 unk_28A_5 : 4;
    u16 overshot : 1;
    u16 unk_28A_10 : 6;
    u8 pad_28c[0x10];
    fx32 moveSpeed;
    fx32 moveAccel;
    u8 pad_2a4[0x28];
    VecFx32 targetPosition;
} MovingActor;

extern fx32 ApplyActorScaleFactors(MovingActor *actor);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void ApplyActorMoveSpeed(MovingActor *actor, const VecFx32 *direction, fx32 stopDistance, VecFx32 *position)
{
    fx32 scale;
    fx32 speed;
    fx32 accel;

    scale = ApplyActorScaleFactors(actor);
    speed = FX_Mul(actor->moveSpeed, scale);
    accel = FX_Mul(actor->moveAccel, scale);
    if (speed != 0) {
        if (actor->ignoreStopDistance || stopDistance > (speed < 0 ? -speed : speed)) {
            VEC_MultAdd(speed, direction, position, position);
            actor->moveSpeed += accel;
            if (actor->moveSpeed < 0) {
                actor->moveSpeed = 0;
                actor->moveAccel = 0;
            }
        } else if (!actor->overshootTarget) {
            position->x = actor->targetPosition.x;
            position->z = actor->targetPosition.z;
            if ((actor->snapMode & 2) || (actor->behaviorFlags & 8)) {
                position->y = actor->targetPosition.y;
            }
            actor->moveSpeed = 0;
            actor->moveAccel = 0;
        } else {
            actor->overshot = TRUE;
            VEC_MultAdd(speed, direction, position, position);
        }
    }
}
