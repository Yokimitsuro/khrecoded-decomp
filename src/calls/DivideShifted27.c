#include "nitro/types.h"

extern s64 _ll_sdiv(s64 numerator, s64 denominator);

s64 DivideShifted27(s32 numerator, s32 denominator)
{
    return _ll_sdiv((s64)numerator << 27, denominator);
}
