#include "nitro/types.h"

BOOL IsFlag10Set(int *flags)
{
    return (*flags & 0x10) > 0;
}
