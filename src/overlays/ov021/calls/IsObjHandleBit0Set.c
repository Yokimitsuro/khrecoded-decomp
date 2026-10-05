#include "nitro/types.h"

BOOL IsObjHandleBit0Set(u32 *flags)
{
    return (*flags & 1) != 0;
}
