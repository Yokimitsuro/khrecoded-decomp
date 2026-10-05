#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

BOOL IsVecZero(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}
