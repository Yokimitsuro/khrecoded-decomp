#include "nitro/types.h"

typedef struct CameraSwing {
    s32 unk00;
    s32 duration;
    s32 angle;
    s32 speed;
    s32 accel;
    s32 elapsed;
} CameraSwing;

extern u32 random_next_scaled(u32 upperBound);

void InitRandomCameraSwing(CameraSwing *swing)
{
    s32 angle;
    if (random_next_scaled(2) != 0) {
        angle = 0;
    } else {
        angle = 0xb4000;
    }
    swing->angle = angle;
    swing->speed = 0x2b8;
    swing->accel = 0x333;
    swing->elapsed = 0;
    swing->duration = 0xa000;
}
