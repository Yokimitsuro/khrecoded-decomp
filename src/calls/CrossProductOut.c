#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void CrossProductOut(VecFx32 *dst, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 tmp;
    func_01ff9ea8(a, b, &tmp);
    *dst = tmp;
}
