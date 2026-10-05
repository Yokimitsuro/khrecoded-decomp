#include "nitro/types.h"

extern int data_0206038c;
extern s8 data_02060389;

int ClampValueByMode(int value, int index)
{
    int mode = *((int *)&data_0206038c + index);
    s8 limit;
    switch (mode) {
    case 0:
        return value;
    case 1:
        limit = *((s8 *)&data_02060389 + index);
        if (value > limit) {
            value = limit;
        }
        return value;
    case 2:
        limit = *((s8 *)&data_02060389 + index);
        if (value < limit) {
            value = limit;
        }
        return value;
    default:
        return value;
    }
}
