#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void GetPerpendicularVector(VecFx32 *out, VecFx32 *v, s32 param3, s32 param4);
extern void NormalizeVectorInto(VecFx32 *dest, const VecFx32 *src);

void ComputeNormalizedCrossInto(VecFx32 *dest, VecFx32 *v, s32 param3, s32 param4)
{
    VecFx32 normalized;
    VecFx32 raw;
    GetPerpendicularVector(&raw, v, param3, param4);
    NormalizeVectorInto(&normalized, &raw);
    *dest = normalized;
}
