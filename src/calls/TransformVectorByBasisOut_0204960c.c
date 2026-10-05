#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 row[3];
} Basis3x3;

extern void TransformVectorByBasis(const VecFx32 *vec, const Basis3x3 *basis, VecFx32 *out);

void TransformVectorByBasisOut_0204960c(VecFx32 *dst, const VecFx32 *vec, const Basis3x3 *basis)
{
    VecFx32 tmp;
    TransformVectorByBasis(vec, basis, &tmp);
    *dst = tmp;
}
