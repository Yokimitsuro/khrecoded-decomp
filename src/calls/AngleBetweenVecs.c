#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern u16 Math_AcosIdx(int cosine);

s16 AngleBetweenVecs(const VecFx32 *a, const VecFx32 *b)
{
    fx32 cosine = VEC_DotProduct(a, b);

    if (cosine == FX32_ONE) {
        return 0;
    }
    if (cosine > FX32_ONE) {
        cosine = FX32_ONE;
    } else if (cosine < -FX32_ONE) {
        cosine = -FX32_ONE;
    }
    return Math_AcosIdx(cosine);
}
