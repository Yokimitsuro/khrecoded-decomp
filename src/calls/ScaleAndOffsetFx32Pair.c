#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 { fx32 x; fx32 y; } Vec2Fx32;

extern Vec2Fx32 ScaleFx32Pair(const Vec2Fx32 *pair, fx32 scale);
extern Vec2Fx32 AddFx32Pair(const Vec2Fx32 *a, const Vec2Fx32 *b);

Vec2Fx32 ScaleAndOffsetFx32Pair(fx32 scale, const Vec2Fx32 *pair, const Vec2Fx32 *offset)
{
    return AddFx32Pair(&ScaleFx32Pair(pair, scale), offset);
}
