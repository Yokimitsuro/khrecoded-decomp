#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct PathCamera {
    VecFx32 position;
    VecFx32 lookDir;
    u8 pad18[0xc];
    VecFx32 anchor;
    VecFx32 targetDir;
    VecFx32 offset;
    fx32 turnRate;
} PathCamera;

extern void Camera_GetRaisedPlayerPosition(VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern void GetUnitRejectionFromAxis(VecFx32 *out, const VecFx32 *vec, const VecFx32 *normal);
extern s16 AngleBetweenVecs(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern void TurnVecTowardVecLimited(VecFx32 *vec, const VecFx32 *target, s32 step);

#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

void TrackPlayerCameraDirection(PathCamera *camera)
{
    VecFx32 player;
    VecFx32 side;
    VecFx32 up;
    VecFx32 projected;
    VecFx32 forwardTmp;
    VecFx32 dir;
    VecFx32 delta;
    VecFx32 deltaArg;
    VecFx32 upTmp;
    VecFx32 sideTmp;
    VecFx32 sideNorm;
    VecFx32 sideArg;
    s32 angle;
    s32 step;

    Camera_GetRaisedPlayerPosition(&player);
    if (camera->anchor.x == player.x && camera->anchor.y == player.y && camera->anchor.z == player.z) {
        forwardTmp.x = FX32_ONE;
        forwardTmp.y = 0;
        forwardTmp.z = 0;
        camera->targetDir = forwardTmp;
    } else {
        VEC_Subtract(&player, &camera->anchor, &delta);
        deltaArg = delta;
        VEC_Normalize(&deltaArg, &dir);
        camera->targetDir = dir;
    }
    upTmp.x = 0;
    upTmp.y = FX32_ONE;
    upTmp.z = 0;
    up = upTmp;
    sideTmp.x = -FX_MUL_ROUND(camera->offset.z, up.y);
    sideTmp.y = 0;
    sideTmp.z = FX_MUL_ROUND(camera->offset.x, up.y);
    sideArg = sideTmp;
    VEC_Normalize(&sideArg, &sideNorm);
    side = sideNorm;
    GetUnitRejectionFromAxis(&projected, &camera->targetDir, &side);
    camera->targetDir = projected;
    angle = (s32)(((s64)AngleBetweenVecs(&camera->lookDir, &camera->targetDir) * 0x6488) / 0x10000);
    if (angle < 0x10) {
        angle = 0x10;
    }
    step = FX_Mul(angle, camera->turnRate);
    if (step > 0x595) {
        step = 0x595;
    } else if (step < 0x47) {
        step = 0x47;
    }
    TurnVecTowardVecLimited(&camera->lookDir, &camera->targetDir, step);
}
