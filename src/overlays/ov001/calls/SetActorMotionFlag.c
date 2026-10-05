#include "nitro/types.h"

void SetActorMotionFlag(u8 *actor, u32 flag)
{
    *(u32 *)(actor + 0x2a4) = flag;
}
