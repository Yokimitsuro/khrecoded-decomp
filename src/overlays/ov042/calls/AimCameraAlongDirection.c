#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void AimCameraAlongDirection(const VecFx32 *direction) {
    u8 *camera = data_ov042_020be5e0;
    VecFx32 goalTarget;
    VecFx32 target;
    VEC_MultAdd(VEC_Distance((VecFx32 *)(camera + 0x20), (VecFx32 *)(camera + 0x14)), direction, (VecFx32 *)(camera + 0x14), &goalTarget);
    *(VecFx32 *)(camera + 0x20) = goalTarget;
    VEC_MultAdd(VEC_Distance((VecFx32 *)(camera + 0x88), (VecFx32 *)(camera + 0x94)), direction, (VecFx32 *)(camera + 0x94), &target);
    *(VecFx32 *)(camera + 0x88) = target;
}
