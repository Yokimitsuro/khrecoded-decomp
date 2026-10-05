#include "nitro/types.h"

extern BOOL AnySubObjectFlagsActive(int entity);

int GetTransitionReaction(int entity, int from, int to)
{
    int result = 0;
    if (from == to || to == -1) {
        return 0;
    }
    switch (from) {
    case 12:
        if (to != 4 && to != 3) {
            result = 5;
            if (to == 11) {
                result = 3;
            }
        }
        if (to == 16) {
            result = 10;
        }
        break;
    case 16:
        result = 2;
        break;
    case 1:
        switch (to) {
        case 12:
            result = 10;
            break;
        case 0:
            if (!AnySubObjectFlagsActive(entity)) {
                result = 5;
            } else {
                result = 10;
            }
            break;
        default:
            result = 5;
            break;
        }
        break;
    case 15:
        result = 10;
        break;
    case 14:
        result = 6;
        break;
    case 23:
        if (to != 12) {
            result = 5;
        } else {
            result = 2;
        }
        break;
    case 0:
        if (to < 45) {
            result = 5;
        }
        if (to >= 30 && to < 67) {
            result = 5;
        }
        break;
    }
    return result;
}


