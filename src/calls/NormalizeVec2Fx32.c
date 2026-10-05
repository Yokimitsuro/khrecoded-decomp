#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern fx32 FX_Sqrt(fx32 value);
extern fx32 FX_Div(fx32 numer, fx32 denom);

void NormalizeVec2Fx32(Vec2Fx32 *out, const Vec2Fx32 *vec, fx32 *outLength)
{
    Vec2Fx32 result;
    fx32 x;
    fx32 y;

    *outLength = FX_Sqrt((fx32)(((fx64)vec->x * vec->x + (fx64)vec->y * vec->y) >> 12));
    y = FX_Div(vec->y, *outLength);
    x = FX_Div(vec->x, *outLength);
    result.x = x;
    result.y = y;
    *out = result;
}
