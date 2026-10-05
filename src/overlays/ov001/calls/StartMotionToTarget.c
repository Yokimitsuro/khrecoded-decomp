#include "nitro/types.h"

extern void ComputeArcTrajectory(void *dstMotion, void *curPos, void *target, u32 speed, u32 flag);

void StartMotionToTarget(u8 *actor, void *target, u32 speed, u32 flag)
{
    ComputeArcTrajectory(actor + 0x33c, actor + 0x2c0, target, speed, flag);
    *(u32 *)(actor + 0x360) = 0;
    *(u32 *)(actor + 0x364) = flag;
}
