#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void AddVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add(a, b, &result);
    *out = result;
}
