#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 axes[3];
} Basis;

extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);

void CombineBasisAxes(const Basis *basis, const fx32 *weights, VecFx32 *out, VecFx32 *partial)
{
    VecFx32 scaled = basis->axes[0];

    ScaleVecFx32InPlace(&scaled, weights[0]);
    *out = scaled;
    VEC_MultAdd(weights[1], &basis->axes[1], out, out);
    *partial = *out;
    VEC_MultAdd(weights[2], &basis->axes[2], out, out);
}
