#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32(VecFx32 *vec);

void NegateVecFx32Into(VecFx32 *dest, const VecFx32 *src)
{
    VecFx32 tmp = *src;
    NegateVecFx32(&tmp);
    *dest = tmp;
}
