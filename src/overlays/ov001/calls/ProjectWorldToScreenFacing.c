#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int func_02028c38(const VecFx32 *world, int *x, int *y);
extern const VecFx32 *func_02028c20(void);
extern const VecFx32 *func_02028c2c(void);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);

void ProjectWorldToScreenFacing(const VecFx32 *world, int *x, int *y)
{
    VecFx32 viewDir;
    VecFx32 toWorld;
    const VecFx32 *cameraPos;

    func_02028c38(world, x, y);
    cameraPos = func_02028c20();
    VEC_Subtract(func_02028c2c(), cameraPos, &viewDir);
    VEC_Subtract(world, cameraPos, &toWorld);
    if (VEC_DotProduct(&viewDir, &viewDir) != 0 && VEC_DotProduct(&toWorld, &toWorld) != 0) {
        VEC_Normalize(&viewDir, &viewDir);
        VEC_Normalize(&toWorld, &toWorld);
        if (VEC_DotProduct(&viewDir, &toWorld) < 0) {
            *x = 255 - *x;
            *y = 191 - *y;
        }
    }
}
