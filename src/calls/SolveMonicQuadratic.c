#include "nitro/types.h"
#include "nitro/fx_types.h"

fx32 FX_Sqrt(fx32 value);

void SolveMonicQuadratic(fx32 linear, fx32 constant, fx32 *rootHigh, fx32 *rootLow)
{
    fx32 discriminant = (fx32)(((s64)linear * linear + 0x800) >> 12) - constant * 4;
    fx32 root;

    /* Roots of x^2 + linear*x + constant */
    if (discriminant >= 0) {
        root = FX_Sqrt(discriminant);
        if (rootHigh != NULL)
            *rootHigh = (root - linear) / 2;
        if (rootLow != NULL)
            *rootLow = -(linear + root) / 2;
        return;
    }
    if (rootHigh != NULL)
        *rootHigh = 0x7fffffff;
    if (rootLow != NULL)
        *rootLow = 0x7fffffff;
}

