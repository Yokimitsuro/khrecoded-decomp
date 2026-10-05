#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Div(fx32 a, fx32 b);

fx32 SafeFixedRatio(fx32 numerator, fx32 denominator)
{
    if (denominator == 0) {
        return 0;
    }
    if (numerator == denominator) {
        return 0x1000;
    }
    return FX_Div(numerator, denominator);
}
