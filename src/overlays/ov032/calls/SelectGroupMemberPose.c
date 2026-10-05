#include "nitro/types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x2b];
    u8 objectIndex;
    u8 pad_34[0x43];
    u8 defaultPose;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 pose : 5;
    u32 nextPose : 5;
    u32 unk_00_28 : 4;
    u32 unk_04_0 : 8;
    u32 cooldown : 8;
    u32 memberTotal : 8;
    u32 unk_04_24 : 8;
    u8 pad_08[0xc];
    u16 transitionTimer;
    u8 pad_16[0x22];
    s16 idleTime;
} ObjectGroup;

extern const u8 data_ov032_020bff8c[];

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern BOOL func_ov032_020bf0a8(void *world, int groupIndex);
extern u32 random_next_scaled(u32 upperBound);

u32 SelectGroupMemberPose(GroupObject *object, int threshold)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);
    u32 pose = object->defaultPose;

    if (func_ov032_020bf0a8(object->world, work->groupIndex)) {
        if (group->idleTime > 0xf0 && random_next_scaled(6) == 0) {
            return data_ov032_020bff8c[random_next_scaled(8)];
        }
        return group->pose;
    }
    if (group->leaderIndex == object->objectIndex) {
        if (group->cooldown != 0) {
            pose = data_ov032_020bff8c[(group->cooldown >> 2) & 7];
        } else {
            pose = 0x14;
        }
    } else if (group->transitionTimer != 0) {
        u32 elapsed = 0x1e - group->transitionTimer;
        u32 total = group->memberTotal;
        if ((int)((elapsed * total / 0x1e * 3) % total) > threshold) {
            pose = group->nextPose;
        } else {
            pose = group->pose;
        }
    }
    return pose;
}
