#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ArcTrajectory {
    VecFx32 position;
    VecFx32 velocity;
    fx32 unk18;
    fx32 gravity;
} ArcTrajectory;

extern fx32 FX_Mul(fx32 left, fx32 right);
extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void ComputeArcTrajectory(ArcTrajectory *arc, const VecFx32 *start, const VecFx32 *target, fx32 height, fx32 duration)
{
    VecFx32 direction;
    VecFx32 apex;
    fx32 distance;
    fx32 apexDistance;
    fx32 speed;
    fx32 ratio;
    fx32 dx;
    fx32 dz;
    fx32 apexTime;
    fx32 velocityY;
    fx32 peakY;
    fx32 gravity;

    peakY = start->y + height;
    dx = target->x - start->x;
    dz = target->z - start->z;
    distance = FX_Sqrt(FX_Mul(dx, dx) + FX_Mul(dz, dz));
    if (distance < 0x80) {
        distance = 0x80;
    }
    ratio = FX_Sqrt(FX_Div(start->y - peakY, target->y - peakY));
    apexDistance = FX_Mul(ratio, distance);
    if (0x1000 - ratio == 0) {
        apexDistance = 0;
    } else {
        apexDistance = FX_Div(-apexDistance, 0x1000 - ratio);
    }
    if (apexDistance <= 0 || apexDistance >= distance) {
        apexDistance = FX_Mul(ratio, distance);
        if (ratio + 0x1000 == 0) {
            apexDistance = 0;
        } else {
            apexDistance = FX_Div(apexDistance, ratio + 0x1000);
        }
        if (apexDistance <= 0 || apexDistance >= distance) {
            apexDistance = 0;
        }
    }
    direction.x = dx;
    gravity = 0;
    direction.y = 0;
    direction.z = dz;
    func_01ffaff4(&direction, &direction);
    VEC_MultAdd(apexDistance, &direction, start, &apex);
    apex.y = peakY;
    apexTime = FX_Mul(duration, FX_Div(apexDistance, distance));
    {
        fx32 rise = (start->y - apex.y) * 2;
        fx32 timeSquared = FX_Mul(apexTime, apexTime);

        if (timeSquared != 0) {
            gravity = FX_Div(rise, timeSquared);
        }
    }
    velocityY = FX_Mul(-gravity, apexTime);
    if (duration == 0) {
        speed = 0;
    } else {
        speed = FX_Div(distance, duration);
    }
    arc->velocity.x = FX_Mul(speed, direction.x);
    arc->velocity.z = FX_Mul(speed, direction.z);
    arc->velocity.y = velocityY;
    arc->gravity = gravity;
    arc->position = *start;
}
