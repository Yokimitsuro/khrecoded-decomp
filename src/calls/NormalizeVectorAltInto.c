#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);

void NormalizeVectorAltInto(VecFx32 *dest, const VecFx32 *src)
{
    VecFx32 tmp;
    func_01ffaff4(src, &tmp);
    *dest = tmp;
}
