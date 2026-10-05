#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void VecToYawPitch(VecFx32 *dir, s16 *pitch, u16 *yaw)
{
    VecFx32 planar;
    VecFx32 full;
    s32 angle;

    if (yaw != NULL) {
        *yaw = FX_Atan2Idx(dir->x, dir->z);
    }
    if (pitch != NULL) {
        planar.x = dir->x;
        planar.y = 0;
        planar.z = dir->z;
        full.x = dir->x;
        full.y = dir->y;
        full.z = dir->z;
        angle = 0x4000000 - VEC_DotProduct(&planar, &full) * 0x4000;
        if (dir->y > 0) {
            angle = -angle;
            angle += 0xFFFF000;
        }
        *pitch = angle >> 12;
    }
}
