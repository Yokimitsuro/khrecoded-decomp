#include "nitro/fx_types.h"

void ScaleVectorXZ(VecFx32 *out, const VecFx32 *in, fx32 scale)
{
    VecFx32 result;
    result.x = in->x * scale / 4096;
    result.y = in->y;
    result.z = in->z * scale / 4096;
    *out = result;
}
