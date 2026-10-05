#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void SubtractVecFx32Out(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract(a, b, &result);
    *out = result;
}
