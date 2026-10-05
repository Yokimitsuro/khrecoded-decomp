#pragma thumb on

#include "nitro/fx_types.h"

extern fx32 FX_Mul(fx32 a, fx32 b);

fx32 Anim_InterpEased(fx32 t, fx32 p0, fx32 p1, fx32 p2)
{
    if (t <= 0x1000) {
        fx32 a = FX_Mul(-3 * p0 + p1 * 4 - p2, t);
        fx32 b = FX_Mul(p2 + (p0 - (p1 << 1)), FX_Mul(t, t));

        return FX_Mul(0x800, p0 + p0 + a + b);
    } else {
        fx32 two = p1 << 1;
        fx32 c = FX_Mul(p2 - p0, t - 0x1000);

        return FX_Mul(0x800, two + c + FX_Mul(p2 + (p0 - two), FX_Mul(t - 0x1000, t - 0x1000)));
    }
}
