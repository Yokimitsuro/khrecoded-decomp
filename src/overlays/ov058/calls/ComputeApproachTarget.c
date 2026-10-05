#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x24];
    s32 arrived;
} CameraTrackState;

extern const VecFx32 data_ov058_020d89bc;
extern CameraTrackState data_ov058_020d8a44;
extern VecFx32 data_ov058_020d8a4c;

extern int GetSceneSlotAngle(int mode);
extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, int angle, const VecFx32 *offset);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);

void ComputeApproachTarget(VecFx32 *out, int mode)
{
    CameraTrackState *state = &data_ov058_020d8a44;
    VecFx32 target;
    VecFx32 diff;
    VecFx32 offset = data_ov058_020d89bc;

    RotateOffsetAroundY(&target, &data_ov058_020d8a4c, GetSceneSlotAngle(mode), &offset);
    if (mode == 0 && state->arrived == 0) {
        VEC_Subtract(&target, func_ov001_0206dc4c(mode), &diff);
        if (VEC_Mag(&diff) <= 0x19a) {
            state->arrived = 1;
        } else {
            func_01ffaff4(&diff, &diff);
            VEC_MultAdd(0x19a, &diff, &target, &target);
        }
    }
    *out = target;
}
