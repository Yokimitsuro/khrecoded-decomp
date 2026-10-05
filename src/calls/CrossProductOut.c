#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void CrossProductOut(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 tmp;
    VEC_CrossProduct(a, b, &tmp);
    *dst = tmp;
}
