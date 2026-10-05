#include "nitro/types.h"

extern void MI_CpuCopy8(const void *src, void *dest, u32 len);

void ActorObject_SetExtraSlot(u8 *actor, const void *src, int index)
{
    MI_CpuCopy8(src, actor + 0x870 + index * 0xc, 0xc);
}
