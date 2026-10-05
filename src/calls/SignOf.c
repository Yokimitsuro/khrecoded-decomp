#include "nitro/types.h"

int SignOf(int value)
{
    if (value == 0) {
        return 0;
    }
    return value > 0 ? 1 : -1;
}
