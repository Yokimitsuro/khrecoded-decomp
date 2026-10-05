#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupWorld {
    u8 pad_00[0x59];
    u8 kind;
} GroupWorld;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 nextLink;
    u32 unk_08_0 : 5;
    u32 order : 8;
    u32 unk_08_13 : 19;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    GroupWorld *world;
    u8 pad_08[0x2b];
    u8 actorId;
    u8 pad_34[0x4];
    VecFx32 position;
    u8 pad_44[0x2c];
    u16 unk_70_0 : 1;
    u16 isMoving : 1;
    u16 unk_70_2 : 3;
    u16 isUpdated : 1;
    u16 unk_70_6 : 10;
    u8 pad_72[0x4c];
    u8 unk_be_0 : 4;
    u8 phase : 4;
    u8 pad_bf[0x2d];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u32 unk_00;
    u32 mode : 4;
    u32 unk_04_4 : 28;
    u32 needsRebuild : 1;
    u32 needsRefresh : 1;
    u32 unk_08_2 : 3;
    u32 dirty : 1;
    u32 unk_08_6 : 26;
    u16 unk_0c_0 : 8;
    u16 showGauge : 1;
    u16 unk_0c_9 : 7;
    u8 pad_0e[0xe];
    s32 maxHitPoints;
    s32 hitPoints;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(GroupWorld *world, int index);
extern void TickFieldObjectCounters(GroupWorld *world, int groupIndex);
extern void UpdateFieldObjectModeTransition(GroupWorld *world, int groupIndex);
extern void ReleaseCurrentRowHold(GroupObject *object);
extern void func_ov032_020bd9d8(int index, GroupObject *object);
extern void func_ov032_020bde74(GroupObject *object);
extern int UpdateGroupMember(GroupObject *object);
extern void func_ov032_020bf250(GroupObject *object);
extern void UpdateBouncingGroupMember(GroupObject *object);
extern void UpdateGroupChaseState(GroupObject *object);
extern u8 SelectGroupMemberPose(GroupObject *object, int index);
extern BOOL IsRowSettledInMode5(GroupWorld *world, int groupIndex);
extern void func_ov001_02088204(u32 slotIndex, u8 kind, u8 subKind, s32 hitPoints, s32 maxHitPoints, const VecFx32 *position);

int UpdateObjectGroupMembers(GroupObject *object)
{
    ObjectGroup *group;
    GroupObject *member;
    int index;
    GroupMemberWork *work;

    if (object->phase == 6) {
        return 0;
    }
    if (object->phase == 5) {
        return 0;
    }
    if (-1 == object->work->leaderLink) {
        group = func_ov032_020bbc80(object);

        VecFx32 position;
        member = object;
        index = 0;
        position = member->position;
        TickFieldObjectCounters(object->world, object->work->groupIndex);
        if (group->needsRefresh) {
            UpdateFieldObjectModeTransition(object->world, object->work->groupIndex);
        }
        if (group->needsRebuild) {
            ReleaseCurrentRowHold(object);
        }
        if (group->dirty) {
            group->dirty = 0;
        }
        while (member != NULL) {
            work = func_ov032_020bbc98(member);
            switch (group->mode) {
            case 0:
                func_ov032_020bd9d8(index, member);
                break;
            case 1:
                func_ov032_020bde74(member);
                break;
            case 2:
                UpdateGroupMember(member);
                break;
            case 4:
                func_ov032_020bf250(member);
                break;
            case 3:
                UpdateBouncingGroupMember(member);
                break;
            case 5:
                UpdateGroupChaseState(member);
                break;
            }
            member->isUpdated = 1;
            member->isMoving = 0;
            work->order = SelectGroupMemberPose(member, index);
            ++index;
            if (work->nextLink != -1) {
                member = func_ov001_02086384(object->world, work->nextLink);
            } else {
                member = NULL;
            }
        }
        if (IsRowSettledInMode5(object->world, object->work->groupIndex)) {
            position.y = 0x96000;
        }
        if (group->showGauge) {
            func_ov001_02088204(object->work->groupIndex, object->world->kind, object->actorId, group->hitPoints << 3,
                                group->maxHitPoints << 3, &position);
        }
    }
        return 0;
}
