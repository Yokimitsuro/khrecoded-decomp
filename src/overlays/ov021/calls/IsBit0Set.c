#include "nitro/types.h"

BOOL IsBit0Set(u32 *flags)
{
    return (*flags & 1) != 0;
}
