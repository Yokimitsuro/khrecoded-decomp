#include "libs/nitro/fx/fx_types_internal.h"

fx32 FX_Mul(fx32 left, fx32 right)
{
    return (fx32)(((fx64c)left * right + 0x800) >> 12);
}