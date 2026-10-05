#include "nitro/types.h"

int MapKindToSlot(u32 kind)
{
    int slot = -1;

    switch (kind) {
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 19:
        slot = 2;
        break;
    case 0:
    case 1:
    case 2:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        slot = 0;
        break;
    case 14:
        slot = 4;
        break;
    case 15:
        slot = 5;
        break;
    case 16:
        slot = 6;
        break;
    case 17:
        slot = 7;
        break;
    case 18:
        slot = 8;
        break;
    }
    return slot;
}
