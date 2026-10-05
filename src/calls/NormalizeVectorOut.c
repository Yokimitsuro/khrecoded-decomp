#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void NormalizeVectorOut(VecFx32 *dst, const VecFx32 *src)
{
    VecFx32 tmp;
    VEC_Normalize(src, &tmp);
    *dst = tmp;
}
