#include "nitro/types.h"

void ClearActorMotionSpeed(u8 *actor)
{
    *(u32 *)(actor + 0x294) = 0;
}
