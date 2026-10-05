#include "nitro/types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 nextLink;
    s16 prevLink;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x2b];
    u8 objectIndex;
    u8 pad_34[0xb8];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 4;
    u32 phase : 4;
    u32 unk_04_8 : 8;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 isFinished : 1;
    u32 unk_08_1 : 31;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern void func_ov032_020bc168(void *world, int groupIndex);

void UnlinkGroupMember(GroupObject *object)
{
    void *world = object->world;
    GroupObject *prev = NULL;
    GroupObject *next = NULL;
    ObjectGroup *group = func_ov032_020bbc80(object);

    group->memberTotal--;
    func_ov032_020bc168(object->world, object->work->groupIndex);
    if (object->work->prevLink != -1) {
        prev = func_ov001_02086384(world, object->work->prevLink);
    }
    if (object->work->nextLink != -1) {
        next = func_ov001_02086384(world, object->work->nextLink);
    }
    if (next != NULL) {
        next->work->prevLink = (prev == NULL) ? -1 : prev->objectIndex;
    }
    if (prev != NULL) {
        prev->work->nextLink = (next == NULL) ? -1 : next->objectIndex;
    }
    if (group->memberTotal == 1) {
        group->phase = 4;
        group->isFinished = 1;
    }
}
