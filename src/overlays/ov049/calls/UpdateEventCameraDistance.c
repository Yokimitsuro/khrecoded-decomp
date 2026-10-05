#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventCameraWork {
    VecFx32 position;
    u8 pad00c[0x190];
    fx32 distance;
    fx32 targetDistance;
} EventCameraWork;

extern void Camera_GetEventFocusPoint(VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern void VEC_MultAdd(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern int FX_Mul(int left, int right);
extern void func_ov049_020c3ff0(EventCameraWork *work);

void UpdateEventCameraDistance(EventCameraWork *work)
{
    VecFx32 target;
    VecFx32 focus;
    VecFx32 dirArg;
    VecFx32 dir;
    VecFx32 delta;
    VecFx32 deltaArg;
    fx32 goal;
    fx32 diff;
    fx32 absDiff;
    s32 sign;

    Camera_GetEventFocusPoint(&focus);
    target = focus;
    goal = work->targetDistance;
    if (work->distance != goal) {
        diff = goal - work->distance;
        if (diff < 0) {
            absDiff = -diff;
        } else {
            absDiff = diff;
        }
        if (absDiff < 0x10) {
            work->distance = goal;
        } else {
            sign = diff >= 0 ? 1 : -1;
            diff = FX_Mul(diff, 0x4cd);
            work->distance += diff + sign * 0x10;
        }
    }
    VEC_Subtract(&work->position, &target, &delta);
    deltaArg = delta;
    VEC_Normalize(&deltaArg, &dir);
    dirArg = dir;
    VEC_MultAdd(work->distance, &dirArg, &target, &work->position);
    func_ov049_020c3ff0(work);
}
