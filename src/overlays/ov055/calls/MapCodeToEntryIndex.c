#include "nitro/types.h"

int MapCodeToEntryIndex(int code)
{
    int index = -1;
    switch (code) {
    case 5:
        index = 0;
        break;
    case 0x1f:
    case 0x20:
        index = 1;
        break;
    default:
        if (code >= 0x2d && code < 0x60) {
            index = code - 0x2b;
        }
        break;
    }
    return index;
}
