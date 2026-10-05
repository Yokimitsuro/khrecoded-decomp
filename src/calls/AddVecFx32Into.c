#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void AddVecFx32Into(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add(a, b, &result);
    *dest = result;
}
