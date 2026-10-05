#include "nitro/types.h"

extern int *SelectSubObject(void *owner, int which);

int GetSubObjectValue(void *owner, int which, int index)
{
    int result = 0x7fffffff;
    int value = SelectSubObject(owner, which)[index];
    if (value != -0x1000) {
        result = value;
    }
    return result;
}
