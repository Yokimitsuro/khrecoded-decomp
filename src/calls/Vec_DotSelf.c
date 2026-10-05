#include "nitro/fx_types.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void Vec_DotSelf(const VecFx32 *v)
{
    VEC_DotProduct(v, v);
}
