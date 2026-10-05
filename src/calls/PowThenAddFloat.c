#include "nitro/types.h"

extern u32 func_0202441c(u32 a, u32 b);
extern u32 func_0202482c(u32 a, u32 b);

void PowThenAddFloat(u32 base, u32 addend, s32 exponent)
{
    u32 result;
    s32 i;

    i = 1;
    result = base;
    if (1 < exponent) {
        do {
            result = func_0202441c(result, base);
            i = i + 1;
        } while (i < exponent);
    }
    func_0202482c(result, addend);
}
