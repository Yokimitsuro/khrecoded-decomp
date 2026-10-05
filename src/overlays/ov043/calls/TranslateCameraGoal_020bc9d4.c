#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2e0;
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void TranslateCameraGoal_020bc9d4(const VecFx32 *offset) {
    VecFx32 eyeSum;
    VecFx32 targetSum;
    VEC_Add((VecFx32 *)(data_ov043_020bd2e0 + 0x64), offset, &eyeSum);
    *(VecFx32 *)(data_ov043_020bd2e0 + 0x64) = eyeSum;
    VEC_Add((VecFx32 *)(data_ov043_020bd2e0 + 0x58), offset, &targetSum);
    *(VecFx32 *)(data_ov043_020bd2e0 + 0x58) = targetSum;
}
