#include "nitro/types.h"

extern void ReleaseSlotActor(u32 arg);

BOOL HandleCommandKind1(s32 kind, u32 arg)
{
    if (kind == 1) {
        ReleaseSlotActor(arg);
    }
    return TRUE;
}
