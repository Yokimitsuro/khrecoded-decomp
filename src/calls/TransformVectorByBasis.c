#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 row[3];
} Basis3x3;

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

void TransformVectorByBasis(const VecFx32 *vec, const Basis3x3 *basis, VecFx32 *out)
{
    fx32 z = VEC_DotProduct(vec, &basis->row[2]);
    fx32 y = VEC_DotProduct(vec, &basis->row[1]);
    fx32 x = VEC_DotProduct(vec, &basis->row[0]);
    out->x = x;
    out->y = y;
    out->z = z;
}
