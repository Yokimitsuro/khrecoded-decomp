#include "nitro/types.h"
#include "nitro/fx_types.h"

void NegateVecFx32(VecFx32 *vec);
BOOL func_020449c8(void *first, void *second, void *contact, u32 flags, const VecFx32 *velocity);

BOOL SweepCylinderAgainstCylinderSwapped(void *first, void *second, void *contact, u32 options, const VecFx32 *velocity)
{
    u32 flags = (options & 1) ^ 1;
    VecFx32 copy;
    VecFx32 reversed;

    if (options & 4)
        flags |= 8;
    if (options & 8)
        flags |= 4;
    reversed = *velocity;
    NegateVecFx32(&reversed);
    copy = reversed;
    return func_020449c8(second, first, contact, flags, &copy);
}
