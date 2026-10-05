#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov042_020be5e0;
extern void func_01ffaff4(const void *src, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void OffsetCameraColliders(VecFx32 *offset);

void MoveCameraAlongAxis(fx32 distance) {
    VecFx32 offset;
    VecFx32 axis;
    VecFx32 scaled;
    func_01ffaff4(data_ov042_020be5e0 + 0x11c, &axis);
    scaled = axis;
    ScaleVecFx32InPlace(&scaled, distance);
    offset = scaled;
    OffsetCameraColliders(&offset);
}
