#include "nitro/types.h"

int MapStateToEvenIndex(int *state)
{
    switch (*state) {
    case 0:
        break;
    case 1:
    case 2:
        return 0;
    case 3:
        return 2;
    case 4:
        return 4;
    }
    return 0;
}
