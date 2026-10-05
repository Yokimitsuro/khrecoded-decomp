#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    s32 kind;
    u8 flags;
} Container;

BOOL Container_IsOperationAllowed(Container *obj)
{
    if ((obj->kind == 4) && ((obj->flags & 2) != 0)) {
        return FALSE;
    }
    return TRUE;
}
