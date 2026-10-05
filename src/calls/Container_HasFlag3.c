#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
} Container;

BOOL Container_HasFlag3(Container *obj)
{
    return (obj->flags & 8) != 0;
}
