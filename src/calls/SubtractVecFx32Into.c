#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void SubtractVecFx32Into(VecFx32 *dest, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract(a, b, &result);
    *dest = result;
}
