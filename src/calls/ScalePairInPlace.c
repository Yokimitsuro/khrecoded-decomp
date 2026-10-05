#include "nitro/types.h"
#include "nitro/fx_types.h"

static inline fx32 RoundMul12(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 0xc);
}

void ScalePairInPlace(fx32 *pair, fx32 scale)
{
    pair[0] = RoundMul12(pair[0], scale);
    pair[1] = RoundMul12(pair[1], scale);
}
