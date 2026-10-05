#include "nitro/types.h"

extern void GetStageActor(s16 groupId);
extern void GetStageObjectHandle(u16 targetId);

BOOL NotifyActorGroupAndTarget(u8 *actor)
{
    GetStageActor(*(s16 *)(actor + 0x10));
    GetStageObjectHandle(*(u16 *)(actor + 0x12));
    return FALSE;
}
