#include "nitro/types.h"

double MSL_Fabs(double x, double y) {
    u32 *p = (u32 *)&x;
    p[1] &= 0x7fffffff;
    return x;
}
