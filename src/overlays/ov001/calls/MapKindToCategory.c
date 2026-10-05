#include "nitro/types.h"

int MapKindToCategory(int kind)
{
    int result = 0;

    switch (kind) {
    case 1:
        result = 4;
        break;
    case 2:
        result = 11;
        break;
    case 3:
        result = 11;
        break;
    case 4:
        result = 5;
        break;
    case 5:
        result = 13;
        break;
    case 6:
        result = 1;
        break;
    case 7:
        result = 1;
        break;
    case 8:
        result = 2;
        break;
    case 9:
        result = 2;
        break;
    case 10:
        result = 12;
        break;
    case 11:
        result = 6;
        break;
    case 12:
        result = 6;
        break;
    case 13:
        result = 14;
        break;
    case 14:
        result = 3;
        break;
    case 15:
        result = 3;
        break;
    case 16:
        result = 3;
        break;
    case 17:
        result = 3;
        break;
    case 18:
        result = 15;
        break;
    case 19:
        result = 43;
        break;
    case 20:
        result = 8;
        break;
    case 21:
        result = 8;
        break;
    case 22:
    case 23:
    case 24:
    case 25:
        result = 0;
        break;
    case 26:
        result = 10;
        break;
    case 27:
        result = 10;
        break;
    case 28:
        result = 9;
        break;
    case 29:
        result = 9;
        break;
    }
    return result;
}
