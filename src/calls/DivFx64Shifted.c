#include "nitro/types.h"

extern s64 _ll_sdiv(s64 numerator, s64 denominator);

s64 DivFx64Shifted(s64 numerator, s64 denominator)
{
    return _ll_sdiv(numerator << 16, denominator << 16);
}
