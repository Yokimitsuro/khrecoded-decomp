#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct BasisMatrix {
    VecFx32 row[3];
} BasisMatrix;

extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *dest);

void BuildBasisMatrix(const VecFx32 *forward, const VecFx32 *up, BasisMatrix *out)
{
    out->row[0] = *forward;
    VEC_CrossProduct(up, forward, &out->row[1]);
    VEC_Normalize(&out->row[1], &out->row[1]);
    VEC_CrossProduct(forward, &out->row[1], &out->row[2]);
}
