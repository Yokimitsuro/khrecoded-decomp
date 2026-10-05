#include "nitro/types.h"

extern BOOL func_ov001_0206e31c(void);

int MapKindToSlotIndex(int kind)
{
    int result = -1;

    switch (kind) {
    case 5:
        result = 0;
        break;
    case 0xd:
        result = 1;
        break;
    case 10:
        result = 4;
        break;
    case 0x1f:
        result = 7;
        break;
    case 0x20:
        result = 8;
        break;
    case 0x21:
        result = 9;
        break;
    case 0x22:
        result = 10;
        break;
    case 0x23:
        result = 11;
        break;
    case 0x24:
        result = 12;
        break;
    case 0x25:
        result = 13;
        break;
    case 0x26:
        result = 14;
        break;
    case 0x27:
        result = 15;
        break;
    case 0x28:
        result = 16;
        break;
    case 0x29:
        result = 17;
        break;
    case 0x2a:
        result = 18;
        break;
    case 0x2b:
        result = 19;
        break;
    case 0x17:
        if (func_ov001_0206e31c()) {
            result = 5;
        }
        break;
    case 0x18:
        if (!func_ov001_0206e31c()) {
            result = 2;
        } else {
            result = 6;
        }
        break;
    case 0x19:
        result = 3;
        break;
    default:
        if (kind >= 0x2d && kind < 0x60) {
            result = kind - 0x19;
        }
        break;
    }
    return result;
}
