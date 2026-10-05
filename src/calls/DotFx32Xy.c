#include "nitro/types.h"
#include "nitro/fx_types.h"

fx32 DotFx32Xy(const VecFx32 *a, const VecFx32 *b)
{
    return (fx32)(((s64)a->x * b->x + (s64)a->y * b->y) >> 12);
}
