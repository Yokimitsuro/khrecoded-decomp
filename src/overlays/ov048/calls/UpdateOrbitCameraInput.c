#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct OrbitCamera {
    u8 pad00[0x18];
    VecFx32 position;
    s32 speed;
} OrbitCamera;

extern VecFx32 data_0205344c;
extern u16 data_020604fc;
extern u8 NNS_G3dGlb_cameraMtx[];
extern u32 func_ov046_020c0d98(void);
extern s16 AngleBetweenVecs(const VecFx32 *a, const VecFx32 *b);
extern void NegateVecFx32(VecFx32 *vec);
extern void TransformVectorByBasis(const VecFx32 *vec, const void *basis, VecFx32 *out);
extern void RotateVecTowardVec(VecFx32 *vec, const VecFx32 *axis, s32 angle);

#define SET_UP(v) ((v).x = 0, (v).y = FX32_ONE, (v).z = 0)
#define TO_ANGLE(a) ((s32)(((s64)(a) * 0x6488) / 0x10000))

void UpdateOrbitCameraInput(OrbitCamera *camera)
{
    VecFx32 dir = data_0205344c;
    VecFx32 rotAxis;
    VecFx32 arg1, arg2, arg3, arg4, arg5, arg6;
    VecFx32 up1, up2, axisA, up3, up4, up5, axisB, up6;
    u16 keys = data_020604fc;
    s32 limit;
    s32 baseAngle;
    s32 angle;
    u32 flags;

    if (keys & 0x10) dir.x += FX32_ONE;
    if (keys & 0x20) dir.x -= FX32_ONE;
    if (keys & 0x40) dir.y += FX32_ONE;
    if (keys & 0x80) dir.y -= FX32_ONE;
    if (dir.x == 0 && dir.y == 0 && dir.z == 0) {
        return;
    }
    limit = camera->speed;
    flags = func_ov046_020c0d98();
    if (flags & 8) dir.y = -dir.y;
    if (flags & 0x10) dir.x = -dir.x;
    if (dir.y == 0) {
        SET_UP(up1);
        arg1 = up1;
        baseAngle = TO_ANGLE(AngleBetweenVecs(&camera->position, &arg1));
    }
    if (dir.x == 0) {
        SET_UP(up2);
        axisA = up2;
        if (dir.y < 0) {
            NegateVecFx32(&axisA);
        }
        arg2 = axisA;
        angle = TO_ANGLE(AngleBetweenVecs(&camera->position, &arg2));
        if (limit > angle - 0x596) {
            limit = angle - 0x596;
        }
    }
    if (limit <= 0) {
        return;
    }
    TransformVectorByBasis(&dir, NNS_G3dGlb_cameraMtx, &rotAxis);
    RotateVecTowardVec(&camera->position, &rotAxis, limit);
    if (dir.y == 0) {
        SET_UP(up3);
        arg3 = up3;
        angle = TO_ANGLE(AngleBetweenVecs(&camera->position, &arg3));
        SET_UP(up4);
        arg4 = up4;
        RotateVecTowardVec(&camera->position, &arg4, angle - baseAngle);
    } else {
        s32 sign;
        SET_UP(up5);
        axisB = up5;
        if (dir.y < 0) {
            NegateVecFx32(&axisB);
        }
        arg5 = axisB;
        angle = TO_ANGLE(AngleBetweenVecs(&camera->position, &arg5));
        sign = 0;
        if (angle < 0x596) {
            if (dir.y != 0) {
                if (dir.y > 0) {
                    sign = 1;
                } else {
                    sign = -1;
                }
            }
            SET_UP(up6);
            arg6 = up6;
            RotateVecTowardVec(&camera->position, &arg6, (angle - 0x596) * sign);
        }
    }
}
