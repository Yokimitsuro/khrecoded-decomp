#include "nitro/types.h"

extern u32 WriteSessionPackedBits();

u32 ClearSessionPackedBit(void *object)
{
    return WriteSessionPackedBits(object, 1, 0);
}
