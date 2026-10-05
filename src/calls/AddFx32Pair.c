#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Vec2Fx32 { fx32 x; fx32 y; } Vec2Fx32;

extern void Vec2Add(const Vec2Fx32 *a, const Vec2Fx32 *b, Vec2Fx32 *out);

void AddFx32Pair(Vec2Fx32 *out, const Vec2Fx32 *a, const Vec2Fx32 *b)
{
    Vec2Fx32 tmp;
    Vec2Add(a, b, &tmp);
    *out = tmp;
}
