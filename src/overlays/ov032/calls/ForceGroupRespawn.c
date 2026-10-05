#include "nitro/types.h"

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
} GroupObject;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x10];
    u16 respawnTimer;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern s32 GetRowRespawnLimit(void *world, s32 groupIndex);
extern void SpawnRowChainMembers(void *world, s32 groupIndex, GroupObject *object);

void ForceGroupRespawn(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);

    group->respawnTimer = GetRowRespawnLimit(object->world, work->groupIndex);
    SpawnRowChainMembers(object->world, work->groupIndex, object);
}
