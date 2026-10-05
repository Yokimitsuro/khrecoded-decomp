#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void DivideVecByLength(VecFx32 *vec, fx32 divisor);

VecFx32 VecFx32DividedByScalar(const VecFx32 *vec, fx32 divisor)
{
    VecFx32 result = *vec;
    DivideVecByLength(&result, divisor);
    return result;
}
