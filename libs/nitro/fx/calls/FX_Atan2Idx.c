#include "libs/nitro/fx/fx_types_internal.h"

extern fx32 FX_Div(fx32 numerator, fx32 denominator);
extern const s16 FX_AtanIdxTable_[129];

u16 FX_Atan2Idx(fx32 y, fx32 x)
{
    fx32 numerator, denominator;
    int base;
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
                base = 16384;
                add = 0;
            } else {
                return (u16)8192;
            }
        } else if (x < 0) {
            x = -x;
            if (x < y) {
                numerator = x;
                denominator = y;
                base = 16384;
                add = 1;
            } else if (x > y) {
                numerator = y;
                denominator = x;
                base = 32768;
                add = 0;
            } else {
                return (u16)24576;
            }
        } else {
            return (u16)16384;
        }
    } else if (y < 0) {
        y = -y;
        if (x < 0) {
            x = -x;
            if (x > y) {
                numerator = y;
                denominator = x;
                base = -32768;
                add = 1;
            } else if (x < y) {
                numerator = x;
                denominator = y;
                base = -16384;
                add = 0;
            } else {
                return (u16)-24576;
            }
        } else if (x > 0) {
            if (x < y) {
                numerator = x;
                denominator = y;
                base = -16384;
                add = 1;
            } else if (x > y) {
                numerator = y;
                denominator = x;
                base = 0;
                add = 0;
            } else {
                return (u16)-8192;
            }
        } else {
            return (u16)-16384;
        }
    } else {
        if (x >= 0) {
            return 0;
        } else {
            return (u16)32768;
        }
    }

    if (denominator == 0) {
        return 0;
    }
    if (add) {
        return (u16)(base + FX_AtanIdxTable_[FX_Div(numerator, denominator) >> 5]);
    } else {
        return (u16)(base - FX_AtanIdxTable_[FX_Div(numerator, denominator) >> 5]);
    }
}