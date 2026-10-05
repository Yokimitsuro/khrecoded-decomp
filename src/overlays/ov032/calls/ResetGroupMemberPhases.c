#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x12];
    s32 unk_18;
    s32 phaseOffset;
    s32 unk_20;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 16;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 isFinished : 1;
    u32 unk_08_1 : 2;
    u32 isFalling : 1;
    u32 unk_08_4 : 28;
    u16 memberCount : 8;
    u16 unk_0C_8 : 8;
    u8 pad_0E[0x2A];
    s16 unk_38;
} ObjectGroup;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern BOOL func_ov016_020a6a84(GroupObject *object);

void ResetGroupMemberPhases(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    int slot = 0;
    int i;

    for (i = 0; i < group->memberCount; i++) {
        GroupObject *member = func_ov001_02086384(object->world, group->firstMember + i);
        GroupMemberWork *work = func_ov032_020bbc98(member);
        if (!func_ov016_020a6a84(member)) {
            work->state = 0;
            work->unk_20 = 0;
            work->unk_18 = 0;
            if (work->leaderLink != -1) {
                func_ov032_020bbc98(func_ov001_02086384(object->world, work->leaderLink));
                work->phaseOffset = slot * 0x1800;
            } else {
                work->phaseOffset = group->memberTotal * 0x1800;
            }
            slot++;
        }
    }
    group->isFalling = 0;
    group->unk_38 = 0;
}
