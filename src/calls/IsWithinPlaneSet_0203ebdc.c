#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 *func_ov021_020af5d4(void);
extern VecFx32 *func_ov021_020af71c(void);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);

BOOL IsWithinPlaneSet_0203ebdc(VecFx32 *point, s32 threshold)
{
    VecFx32 *basePos;
    VecFx32 direction;
    VecFx32 diffTemp;
    VecFx32 *planes;
    u8 i;

    basePos = func_ov021_020af5d4();
    func_01ff9e3c(point, basePos, &diffTemp);
    direction = diffTemp;

    planes = func_ov021_020af71c();
    i = 0;
    do {
        if (VEC_DotProduct(&planes[i], &direction) > threshold) {
            return FALSE;
        }
        i = (i + 1) & 0xff;
    } while (i < 4);

    return TRUE;
}
