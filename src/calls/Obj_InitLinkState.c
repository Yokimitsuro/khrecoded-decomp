#include "nitro/types.h"

typedef struct {
    u32 flags;
    u32 pad_04[0x52];
    s32 slot;
} LinkState;

BOOL Obj_InitLinkState(LinkState *link)
{
    link->flags = 0x30;
    link->slot = -1;
    return TRUE;
}
