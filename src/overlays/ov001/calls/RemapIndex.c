#include "nitro/types.h"

u32 RemapIndex(u32 value)
{
    u32 result;

    result = 0;
    switch (value) {
    case 7:
        result = 2;
        break;
    case 6:
        result = 1;
        break;
    case 11:
        result = 4;
        break;
    case 8:
        result = 3;
        break;
    case 9:
        result = 5;
        break;
    case 10:
        result = 6;
        break;
    case 5:
        result = 7;
        break;
    }
    return result;
}
