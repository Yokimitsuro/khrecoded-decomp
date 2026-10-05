#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 func_0203f28c(fx32 a, fx32 b);

s64 SquareFx32ToFx64(fx32 value)
{
    return func_0203f28c(value, value);
}
