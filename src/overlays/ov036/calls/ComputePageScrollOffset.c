#include "nitro/types.h"

int ComputePageScrollOffset(int from, int to, BOOL forward)
{
    int delta = to - from;

    if (delta == -1 && from % 2 == 1 && forward) {
        delta = 2;
    } else if (from % 2 == 0 && to % 2 == 1) {
        delta -= forward ? 1 : -1;
    }
    if (forward) {
        return delta * 8 / 2;
    }
    return -(delta * 8 / 2);
}
