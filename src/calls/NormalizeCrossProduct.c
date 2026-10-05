#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void ComputeCrossProduct(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void NormalizeVectorInto(VecFx32 *out, const VecFx32 *src);

void NormalizeCrossProduct(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 normalized;
    VecFx32 cross;

    ComputeCrossProduct(&cross, a, b);
    NormalizeVectorInto(&normalized, &cross);
    *out = normalized;
}
