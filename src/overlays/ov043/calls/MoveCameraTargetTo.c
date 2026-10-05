#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2e0;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void TranslateCameraTarget_020bc92c(VecFx32 *offset);

void MoveCameraTargetTo(const VecFx32 *pos) {
    VecFx32 offset;
    VecFx32 delta;
    VEC_Subtract(pos, (VecFx32 *)(data_ov043_020bd2e0 + 0x94), &delta);
    offset = delta;
    TranslateCameraTarget_020bc92c(&offset);
}
