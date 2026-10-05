#include "nitro/types.h"

s64 PowFx64DerivativeTimesN(s64 base, int n)
{
    int i;
    s64 result;

    result = base;
    i = 1;
    if (1 < n - 1) {
        do {
            result = (result * base) >> 12;
            i = i + 1;
        } while (i < n - 1);
    }
    return n * result;
}
