#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Subtract(VecFx32 *dst, VecFx32 *src);
extern fx32 VEC_Mag(VecFx32 *vec);
extern void RandomHorizontalVector(fx32 z, VecFx32 *vec);
extern void func_01ffaff4(VecFx32 *dst, VecFx32 *src);

void ComputeFlatDirectionVector(VecFx32 *from, VecFx32 *to, VecFx32 *direction)
{
    VEC_Subtract(to, from);
    direction->y = 0;
    if (VEC_Mag(direction) == 0) {
        RandomHorizontalVector(0x1000, direction);
    }
    func_01ffaff4(direction, direction);
}
