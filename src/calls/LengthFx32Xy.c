#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 func_02049ed0(s64 value, int power);

fx32 LengthFx32Xy(fx32 x, fx32 y)
{
    return (fx32)(func_02049ed0(((s64)x * x + (s64)y * y) << 12, 2) >> 12);
}
