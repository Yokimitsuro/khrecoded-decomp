#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 row[3];
} Basis3x3;

extern void TransformVectorByBasis(const VecFx32 *vec, const Basis3x3 *basis, VecFx32 *out);

void TransformVectorByBasisOut(VecFx32 *out, const VecFx32 *vec, const Basis3x3 *basis)
{
    VecFx32 result;
    TransformVectorByBasis(vec, basis, &result);
    *out = result;
}
