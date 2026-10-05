#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Basis {
    VecFx32 row[3];
} Basis;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

typedef struct CameraShot {
    VecFx32 position;
    VecFx32 direction;
    VecFx32 up;
    fx32 roll;
    VecFx32 normal;
    s32 usesFocus;
    fx32 positionBlend;
    fx32 rotationBlend;
    s32 normalized : 1;
    s32 dirty : 1;
    s32 arc : 1;
} CameraShot;

typedef struct EventCameraWork {
    CameraShot current;
    CameraShot start;
    CameraShot end;
    CameraShot source;
    s32 mode;
    s32 timer;
    s32 duration;
    s32 arcAngle;
    u8 pad120[0x70];
    VecFx32 lookDir;
} EventCameraWork;

extern fx32 EaseProgress(s32 timer, s32 duration, s32 mode);
extern void RotateTowardVector(const VecFx32 *from, const VecFx32 *to, fx32 ratio, VecFx32 *out);
extern void LerpVecFx32Q27InPlace(VecFx32 *current, const VecFx32 *target, s32 t);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void RotateVectorAroundAxis(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern int FX_Mul(int left, int right);
extern void BuildSideBasisMatrix(const VecFx32 *up, const VecFx32 *forward, Basis *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void CameraPath_TransformKey(EventCameraWork *work, void *target);
extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern void func_ov049_020c3ec8(EventCameraWork *work);

#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

void UpdateEventCameraShot(EventCameraWork *work)
{
    VecFx32 pivot;
    VecFx32 rest;
    VecFx32 armArg;
    Basis endBasis;
    Basis curBasis;
    VecFx32 lerpDir;
    VecFx32 lerpPos;
    VecFx32 arm;
    Basis endBuilt;
    Basis endTmp;
    Basis curBuilt;
    Basis curTmp;
    VecFx32 lookTmp;
    VecFx32 lookDelta;
    VecFx32 lookArg;
    Vec2Fx32 coord;
    Vec2Fx32 scaled;
    Vec2Fx32 coordTmp;
    Vec2Fx32 scaledTmp;
    fx32 dotX;
    fx32 dotY;
    fx32 stepX;
    fx32 stepY;
    fx32 t;
    fx32 startRoll;
    fx32 endRoll;

    t = EaseProgress(work->timer, work->duration, work->mode);
    if (work->current.normalized) {
        RotateTowardVector(&work->start.direction, &work->end.direction, t, &work->current.direction);
    } else {
        lerpDir = work->start.direction;
        LerpVecFx32Q27InPlace(&lerpDir, &work->end.direction, t << 15);
        work->current.direction = lerpDir;
    }
    RotateTowardVector(&work->start.up, &work->end.up, t, &work->current.up);
    if (!work->current.dirty) {
        lerpPos = work->start.position;
        LerpVecFx32Q27InPlace(&lerpPos, &work->end.position, t << 15);
        work->current.position = lerpPos;
    } else {
        VEC_Subtract(&work->start.position, &work->end.direction, &pivot);
        RotateVectorAroundAxis(&pivot, &work->current.normal, work->arcAngle);
        VEC_Add(&pivot, &work->end.direction, &pivot);
        VEC_Subtract(&work->end.position, &pivot, &rest);
        VEC_Subtract(&work->start.position, &work->current.direction, &work->current.position);
        RotateVectorAroundAxis(&work->current.position, &work->current.normal, FX_Mul(work->arcAngle, t));
        if (rest.x != 0 || rest.y != 0 || rest.z != 0) {
            VEC_Subtract(&work->end.position, &work->end.direction, &arm);
            armArg = arm;
            BuildSideBasisMatrix(&work->current.normal, &armArg, &endBuilt);
            endTmp = endBuilt;
            *(MtxFx33 *)&endBasis = *(MtxFx33 *)&endTmp;
            BuildSideBasisMatrix(&work->current.normal, &work->current.position, &curBuilt);
            curTmp = curBuilt;
            *(MtxFx33 *)&curBasis = *(MtxFx33 *)&curTmp;
            dotY = VEC_DotProduct(&rest, &endBasis.row[1]);
            dotX = VEC_DotProduct(&rest, &endBasis.row[2]);
            coordTmp.x = dotX;
            coordTmp.y = dotY;
            coord = coordTmp;
            stepY = FX_Mul(coord.y, t);
            stepX = FX_Mul(coord.x, t);
            scaledTmp.x = stepX;
            scaledTmp.y = stepY;
            scaled = scaledTmp;
            VEC_MultAdd(scaled.x, &curBasis.row[2], &work->current.position, &work->current.position);
            VEC_MultAdd(scaled.y, &curBasis.row[1], &work->current.position, &work->current.position);
        }
        VEC_Add(&work->current.position, &work->current.direction, &work->current.position);
    }
    endRoll = work->end.roll;
    startRoll = work->start.roll;
    if (startRoll != endRoll) {
        work->current.roll = FX_MUL_ROUND(startRoll, 0x1000 - t) + FX_MUL_ROUND(endRoll, t);
    }
    if (work->end.usesFocus != 0) {
        CameraPath_TransformKey(work, work);
    }
    if (work->current.normalized) {
        work->lookDir = work->current.direction;
    } else {
        VEC_Subtract(&work->current.direction, &work->current.position, &lookDelta);
        lookArg = lookDelta;
        VEC_Normalize(&lookArg, &lookTmp);
        work->lookDir = lookTmp;
    }
    func_ov049_020c3ec8(work);
}
