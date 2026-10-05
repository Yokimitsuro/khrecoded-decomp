#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void TranslateCameraTarget(VecFx32 *offset);

void PushFromCameraTarget(const VecFx32 *pos) {
    VecFx32 offset;
    VecFx32 delta;
    VEC_Subtract(pos, (VecFx32 *)(data_ov042_020be5e0 + 0x88), &delta);
    offset = delta;
    TranslateCameraTarget(&offset);
}
