#include "nitro/types.h"

void ActorObject_ResetSecondarySlots(u8 *actor)
{
    int index = 0;
    do {
        u8 *slot = actor + index * 8;
        *(u32 *)(slot + 0x820) = 0xffffffff;
        index = index + 1;
        *(u32 *)(slot + 0x824) = 0xffffffff;
    } while (index < 4);
}
