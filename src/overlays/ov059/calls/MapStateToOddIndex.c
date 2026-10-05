#include "nitro/types.h"

int MapStateToOddIndex(int *state)
{
    switch (*state) {
    case 0:
        break;
    case 1:
    case 2:
        return 1;
    case 3:
        return 3;
    case 4:
        return 5;
    }
    return 1;
}
