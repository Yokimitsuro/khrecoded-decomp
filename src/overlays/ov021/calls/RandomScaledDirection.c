#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 data_0205344c;
extern int random_next_scaled(int range);
extern int nextRandom12(void);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 FX_Mul(fx32 a, fx32 b);

void RandomScaledDirection(fx32 scale, VecFx32 *dir)
{
    random_next_scaled(0xffff);
    random_next_scaled(0xffff);
    random_next_scaled(0xffff);
    dir->x = nextRandom12() - 0x800;
    dir->y = nextRandom12() - 0x800;
    dir->z = nextRandom12() - 0x800;
    if (VEC_Mag(dir) >= 0) {
        VEC_Normalize(dir, dir);
    } else {
        *dir = data_0205344c;
    }
    dir->x = FX_Mul(dir->x, scale);
    dir->y = FX_Mul(dir->z, scale);
    dir->z = FX_Mul(dir->z, scale);
}
