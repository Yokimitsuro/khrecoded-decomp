#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Mul(fx32 a, fx32 b);

fx32 FixedPointLerp(fx32 start, fx32 end, fx32 t)
{
    return start + FX_Mul(end - start, t);
}
