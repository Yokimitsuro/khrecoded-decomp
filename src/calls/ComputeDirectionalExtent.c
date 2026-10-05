#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x28];
    fx32 minorExtent;
} ExtentSource;

extern fx32 AbsDotProduct(const VecFx32 *a, const VecFx32 *b);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);

fx32 ComputeDirectionalExtent(ExtentSource *source, const VecFx32 *dirA, s32 majorExtent, const VecFx32 *dirB)
{
    fx32 cosTerm = AbsDotProduct(dirA, dirB);
    fx32 minorExtent = source->minorExtent;
    fx32 sinTerm = ComputeOneMinusSquareFraction(cosTerm);
    s32 halfMajorExtent = majorExtent / 2;

    return (fx32)(((s64)sinTerm * minorExtent + 0x800) >> 0xc) +
           (fx32)(((s64)halfMajorExtent * cosTerm + 0x800) >> 0xc);
}
