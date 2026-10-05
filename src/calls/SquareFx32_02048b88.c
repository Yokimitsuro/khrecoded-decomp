#include "nitro/types.h"

extern s64 MulFx32Rounded(s32 a, s32 b);

s64 SquareFx32_02048b88(s32 value)
{
    return MulFx32Rounded(value, value);
}
