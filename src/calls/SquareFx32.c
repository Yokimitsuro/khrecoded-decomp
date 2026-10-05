#include "nitro/types.h"
#include "nitro/fx_types.h"

fx32 SquareFx32(fx32 x)
{
    return (fx32)(((s64)x * x + 0x800) >> 12);
}
