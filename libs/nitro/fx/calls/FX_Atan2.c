#include "libs/nitro/fx/fx_types_internal.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern const fx16 FX_AtanTable_[129];

fx16 FX_Atan2(fx32 y, fx32 x)
{
    fx32 numerator, denominator, base;
    int add;

    if (y > 0) {
        if (x > 0) {
            if (x > y) {
                numerator = y;
                denominator = x;
                base = 0;
                add = 1;
            } else if (x < y) {
                numerator = x;
                denominator = y;
                base = 6434;
                add = 0;
            } else {
                return (fx16)3217;
            }
        } else if (x < 0) {
            x = -x;
            if (x < y) {
                numerator = x;
                denominator = y;
                base = 6434;
                add = 1;
            } else if (x > y) {
                numerator = y;
                denominator = x;
                base = 12868;
                add = 0;
            } else {
                return (fx16)9651;
            }
        } else {
            return (fx16)6434;
        }
    } else if (y < 0) {
        y = -y;
        if (x < 0) {
            x = -x;
            if (x > y) {
                numerator = y;
                denominator = x;
                base = -12868;
                add = 1;
            } else if (x < y) {
                numerator = x;
                denominator = y;
                base = -6434;
                add = 0;
            } else {
                return (fx16)-9651;
            }
        } else if (x > 0) {
            if (x < y) {
                numerator = x;
                denominator = y;
                base = -6434;
                add = 1;
            } else if (x > y) {
                numerator = y;
                denominator = x;
                base = 0;
                add = 0;
            } else {
                return (fx16)-3217;
            }
        } else {
            return (fx16)-6434;
        }
    } else {
        if (x >= 0) {
            return 0;
        } else {
            return (fx16)12868;
        }
    }

    if (denominator == 0) {
        return 0;
    }
    if (add) {
        return (fx16)(base + FX_AtanTable_[FX_Div(numerator, denominator) >> 5]);
    } else {
        return (fx16)(base - FX_AtanTable_[FX_Div(numerator, denominator) >> 5]);
    }
}