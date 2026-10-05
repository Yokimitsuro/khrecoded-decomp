#include "nitro/types.h"

typedef struct CameraSwing {
    s32 unk00;
    s32 duration;
    s32 angle;
    s32 speed;
    s32 accel;
    s32 spin;
} CameraSwing;

extern u32 random_next_scaled(u32 upperBound);

void InitFastSpinCameraOrbit(CameraSwing *swing)
{
    s32 sign;
    swing->angle = random_next_scaled(0x168000);
    swing->speed = 0x4cd;
    swing->accel = 0x666;
    sign = random_next_scaled(2) != 0 ? 1 : -1;
    swing->spin = sign * 0xf000;
    swing->duration = 0x14000;
}
