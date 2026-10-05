#include "nitro/types.h"

extern void *GetStageActor(s16 groupId);
extern void *GetLinkedStageActor(void *node);
extern void ClearWalkerStepState(void *node);

void ClearActorGroupFlagsAndNotify(u8 *actor)
{
    void *node;

    *(u8 *)(actor + 0x1b4) = 0;
    *(u8 *)(actor + 0x1b5) = 0;
    for (node = GetStageActor(*(s16 *)(actor + 0x10)); node != 0; node = GetLinkedStageActor(node)) {
        ClearWalkerStepState(node);
    }
}
