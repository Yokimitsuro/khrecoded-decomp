#include "nitro/types.h"

int MinOfArray(int count, int *values)
{
    int minValue;
    u8 i;

    minValue = *values;
    i = 1;
    if (1 < count) {
        do {
            if (minValue > values[i]) {
                minValue = values[i];
            }
            i = i + 1;
        } while (i < count);
    }
    return minValue;
}
