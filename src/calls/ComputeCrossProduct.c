#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void ComputeCrossProduct(VecFx32 *out, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct(a, b, &result);
    *out = result;
}
