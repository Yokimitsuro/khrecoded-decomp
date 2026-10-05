#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void BuildBasisFromForward(const VecFx32 *forward, const VecFx32 *up, VecFx32 *basis)
{
    basis[2] = *forward;
    VEC_CrossProduct(up, forward, &basis[0]);
    VEC_Normalize(&basis[0], &basis[0]);
    VEC_CrossProduct(forward, &basis[0], &basis[1]);
}
