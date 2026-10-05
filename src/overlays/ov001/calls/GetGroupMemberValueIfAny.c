#include "nitro/types.h"

extern void *GetStageActor(s16 groupId);
extern u32 GetLinkedEventId(void *node);

u32 GetGroupMemberValueIfAny(s32 groupId)
{
    void *node;

    if (groupId == 0) {
        return 0;
    }
    node = GetStageActor((s16)groupId);
    if (node != 0) {
        return GetLinkedEventId(node);
    }
    return 0;
}
