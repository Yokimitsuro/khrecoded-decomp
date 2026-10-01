#include "libs/nitro/fx/fx_types_internal.h"

fx32 FX_Mul32x64cFunc(fx32 value, fx64c fraction)
{
    fx64c product = fraction * value + 0x80000000LL;
    return (fx32)(product >> 32);
}