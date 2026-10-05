#include "nitro/types.h"

extern u32 func_0202441c(u32 a, u32 b);
extern u32 func_02023aac(s32 value);

void PowDerivativeTimesN(u32 base, s32 n)
{
    s32 i;
    u32 result;
    u32 nFixed;

    result = base;
    i = 1;
    if (1 < n - 1) {
        do {
            result = func_0202441c(result, base);
            i = i + 1;
        } while (i < n - 1);
    }
    nFixed = func_02023aac(n);
    func_0202441c(nFixed, result);
}
