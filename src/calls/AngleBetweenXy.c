#include "nitro/types.h"
#include "nitro/fx.h"

extern fx32 DotFx32Xy(const VecFx32 *a, const VecFx32 *b);
extern u16 Math_AcosIdx(int cosine);

u16 AngleBetweenXy(const VecFx32 *a, const VecFx32 *b)
{
    fx32 cosine = DotFx32Xy(a, b);

    if (cosine > FX32_ONE) {
        cosine = FX32_ONE;
    } else if (cosine < -FX32_ONE) {
        cosine = -FX32_ONE;
    }
    return Math_AcosIdx(cosine);
}
