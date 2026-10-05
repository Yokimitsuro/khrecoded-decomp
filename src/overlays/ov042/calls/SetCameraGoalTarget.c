#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void TranslateCameraGoal(const VecFx32 *offset);

void SetCameraGoalTarget(const VecFx32 *pos) {
    u8 *camera = data_ov042_020be5e0;
    VecFx32 offset;
    VecFx32 delta;
    VEC_Subtract(pos, (VecFx32 *)(camera + 0x64), &delta);
    offset = delta;
    TranslateCameraGoal(&offset);
    *(VecFx32 *)(camera + 0x14) = *(VecFx32 *)(camera + 0x70);
    *(VecFx32 *)(camera + 0x110) = *(VecFx32 *)(camera + 0x64);
    *(VecFx32 *)(camera + 0x20) = *(VecFx32 *)(camera + 0x110);
}
