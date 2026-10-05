#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecFx32Xy {
    fx32 x;
    fx32 y;
} VecFx32Xy;

void Vec2Add(const VecFx32Xy *a, const VecFx32Xy *b, VecFx32Xy *out)
{
    VecFx32Xy first = *a;

    out->x = first.x + b->x;
    out->y = first.y + b->y;
}
