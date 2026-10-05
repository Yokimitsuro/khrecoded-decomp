#include "nitro/types.h"
#include "nitro/fx_types.h"

extern const s16 data_02053580[];
extern u32 random_next_scaled(u32 upperBound);
extern fx32 FX_Mul(fx32 a, fx32 b);

void RandomHorizontalVector(fx32 length, VecFx32 *out)
{
    int angleIndex = (int)random_next_scaled(0x10000) >> 4;

    out->x = FX_Mul(data_02053580[angleIndex], length);
    out->y = 0;
    out->z = FX_Mul(data_02053580[(0x400 - angleIndex) & 0xfff], length);
}
