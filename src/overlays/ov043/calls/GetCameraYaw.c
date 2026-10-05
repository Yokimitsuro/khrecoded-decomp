#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_ov043_020bd2e0;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FX_Atan2Idx(int vertical_component, int horizontal_component);

u16 GetCameraYaw(void) {
    VecFx32 direction;
    VecFx32 delta;
    VEC_Subtract((VecFx32 *)(data_ov043_020bd2e0 + 0x58), (VecFx32 *)(data_ov043_020bd2e0 + 0x64), &delta);
    direction = delta;
    return FX_Atan2Idx(direction.x, direction.z);
}
