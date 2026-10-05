#include "nitro/types.h"

extern void SwapWord32(int *first, int *second);

void SwapAndNegateSecond(int *first, int *second)
{
    SwapWord32(first, second);
    *second *= -1;
}
