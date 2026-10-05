#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 BlendVectorsBySqrtComplement(VecFx32 *a, const VecFx32 *b, fx32 t, s32 factor, VecFx32 *out);

void BlendVectorsBySqrtComplementPositive(VecFx32 *a, const VecFx32 *b, fx32 t, VecFx32 *out)
{
    BlendVectorsBySqrtComplement(a, b, t, 1, out);
}
