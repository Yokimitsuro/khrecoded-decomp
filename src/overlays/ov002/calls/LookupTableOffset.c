#include "nitro/types.h"

extern int data_ov002_0206aebc[];

int LookupTableOffset(int index, int offset)
{
    int value;
    if (index >= 0x14) {
        index = 0x10;
    }
    value = data_ov002_0206aebc[index];
    if (value != -1) {
        value += offset;
    }
    return value;
}
