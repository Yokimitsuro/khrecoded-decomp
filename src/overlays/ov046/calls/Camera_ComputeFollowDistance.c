#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FollowPreset {
    fx32 distance;
    fx32 height;
    fx32 unk08;
} FollowPreset;

typedef struct FollowControl {
    u8 pad_00[0x30];
    VecFx32 focus;
    u8 pad_3c[0xa4 - 0x3c];
    VecFx32 target;
    fx32 distance;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
    u8 pad_44[0x80 - 0x44];
    s32 type;
    u8 pad_84[0xf0 - 0x84];
    u32 stateFlags;
    u8 pad_f4[0x13c - 0xf4];
    u8 controllerData[4];
} CameraManager;

extern CameraManager *data_ov046_020c3500;
extern FollowPreset data_ov046_020c33d0[];
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL Camera_GetScreenEdgeMask(u32 *edgeMask, const VecFx32 *position, int marginX, int marginY);
extern int FX_Mul(int left, int right);

static inline fx32 ClampFx(fx32 value, fx32 low, fx32 high)
{
    return value > high ? high : (value < low ? low : value);
}

fx32 Camera_ComputeFollowDistance(int preset)
{
    CameraManager *camera = data_ov046_020c3500;
    FollowControl *follow;
    fx32 distance;
    fx32 targetDist;
    int i;
    VecFx32 toFocus;
    VecFx32 toTarget;
    u32 mask;

    follow = camera->type == 0 ? (FollowControl *)camera->controllerData : NULL;
    distance = data_ov046_020c33d0[preset].distance;
    if (follow != NULL && (camera->stateFlags & 0x8000000)) {
        VEC_Subtract(&follow->focus, &camera->eye, &toFocus);
        VEC_Normalize(&toFocus, &toFocus);
        VEC_Subtract(&follow->target, &camera->eye, &toTarget);
        targetDist = func_01ffaff4(&toTarget, &toTarget);
        if (VEC_DotProduct(&toFocus, &toTarget) > 0xa00 && targetDist < 0x50000) {
            for (i = 0; i < 20; i++) {
                if (Camera_GetScreenEdgeMask(&mask, &follow->target, 0, 0) &&
                    Camera_GetScreenEdgeMask(&mask, &follow->target, 20, 20)) {
                    break;
                }
                distance += 0x200;
            }
        } else {
            follow->distance = ClampFx(follow->distance - 0x80, data_ov046_020c33d0[preset].distance, follow->distance);
        }
        if (distance - follow->distance > 0) {
            follow->distance = ClampFx(follow->distance + 0x100, data_ov046_020c33d0[preset].distance, distance);
        }
        distance = follow->distance;
    }
    distance += 0xc00;
    if (camera->stateFlags & 0x80000) {
        distance = FX_Mul(distance, 0x2000);
    }
    return distance;
}


