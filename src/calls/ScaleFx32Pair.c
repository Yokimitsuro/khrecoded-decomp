#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 { fx32 x; fx32 y; } Vec2Fx32;

extern void ScalePairInPlace(Vec2Fx32 *pair, fx32 scale);

void ScaleFx32Pair(Vec2Fx32 *out, const Vec2Fx32 *pair, fx32 scale)
{
    Vec2Fx32 tmp;
    tmp = *pair;
    ScalePairInPlace(&tmp, scale);
    *out = tmp;
}
