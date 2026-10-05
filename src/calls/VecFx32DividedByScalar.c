#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_0204a6c0(VecFx32 *vec, fx32 divisor);

VecFx32 VecFx32DividedByScalar(const VecFx32 *vec, fx32 divisor)
{
    VecFx32 result = *vec;
    func_0204a6c0(&result, divisor);
    return result;
}
