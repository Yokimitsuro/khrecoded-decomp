#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void NegateVecFx32(VecFx32 *vec);

void NegateVecFx32IfNegative(VecFx32 *vec, s32 sign)
{
    if (sign < 0) {
        NegateVecFx32(vec);
    }
}
