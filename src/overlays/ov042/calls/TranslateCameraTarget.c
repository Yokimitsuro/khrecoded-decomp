#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void TranslateCameraTarget(const VecFx32 *offset) {
    VecFx32 eyeSum;
    VecFx32 targetSum;
    VEC_Add((VecFx32 *)(data_ov042_020be5e0 + 0x94), offset, &eyeSum);
    *(VecFx32 *)(data_ov042_020be5e0 + 0x94) = eyeSum;
    VEC_Add((VecFx32 *)(data_ov042_020be5e0 + 0x88), offset, &targetSum);
    *(VecFx32 *)(data_ov042_020be5e0 + 0x88) = targetSum;
}
