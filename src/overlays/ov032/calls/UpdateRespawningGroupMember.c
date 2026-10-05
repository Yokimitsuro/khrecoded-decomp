#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 followLink;
    u32 isMoving : 1;
    u32 unk_08_1 : 3;
    u32 isPushed : 1;
    u32 unk_08_5 : 27;
    u8 pad_0c[0xc];
    VecFx32 offset;
    VecFx32 moveDelta;
    s32 phase;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x30];
    VecFx32 position;
    u8 pad_44[0xA8];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 pose : 5;
    u32 nextPose : 5;
    u32 unk_00_28 : 4;
    u32 unk_04_0 : 4;
    u32 rowState : 4;
    u32 unk_04_8 : 24;
    u32 isFinished : 1;
    u32 unk_08_1 : 1;
    u32 isIdleLong : 1;
    u32 isFalling : 1;
    u32 isAnchored : 1;
    u32 isRespawning : 1;
    u32 unk_08_6 : 26;
    u16 unk_0c;
    u16 respawnDelay;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void ComputeGroupOrbitPosition(GroupObject *object, VecFx32 *target);
extern BOOL ComputePushTowardTarget(const VecFx32 *target, const VecFx32 *center, fx32 *speed, VecFx32 *push);
extern BOOL ProbeFlatGroundSquare(const VecFx32 *center, fx32 length, VecFx32 *out);
extern BOOL TurnTowardOpenDirection(GroupObject *object, VecFx32 *position, fx32 height);
extern void func_ov032_020bbca0(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL UpdateHopWithSpeedRamp(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern u32 random_next_scaled(u32 range);
extern void ForceGroupRespawn(GroupObject *object);
extern void QueueFieldObjectModeChange(void *world, int index, BOOL immediate);
extern void func_ov032_020bbc5c(ObjectGroup *group, GroupMemberWork *work);
extern void MoveGroupObjectAndSyncActor(GroupObject *object, const VecFx32 *delta);

void UpdateRespawningGroupMember(GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group;
    VecFx32 zero;
    VecFx32 delta;
    VecFx32 ground;
    VecFx32 target;
    BOOL landed;
    BOOL moved;

    if (work->leaderLink != -1) {
        return;
    }
    group = func_ov032_020bbc80(object);
    zero = data_0205344c;
    delta = data_0205344c;
    switch (work->state) {
    case 0:
        object->work->state = 0x19;
        break;
    case 0x19:
        if (ProbeFlatGroundSquare(&object->position, 0xc00, &ground)) {
            work->moveDelta = zero;
            work->moveDelta.y = -0x11e;
            object->work->state = 0x1a;
        } else {
            target = *func_ov001_0206dc4c(0);
            ComputeGroupOrbitPosition(object, &target);
            ComputePushTowardTarget(&target, &object->position, &work->phase, &delta);
        }
        break;
    case 0x18:
        if (TurnTowardOpenDirection(object, &object->position, 0xc00)) {
            func_ov032_020bbca0(object->world, work->groupIndex, work->slotIndex, &work->moveDelta);
            object->work->state = 0x1a;
        }
        break;
    case 0x1a:
        landed = FALSE;
        moved = UpdateHopWithSpeedRamp(object->world, work->groupIndex, work, &object->position, &work->moveDelta, 0xc00, &delta, &landed);
        if (landed || random_next_scaled(0x10) == 0) {
            object->work->state = 0x18;
        }
        if (moved) {
            if (group->respawnDelay != 0) {
                group->respawnDelay--;
            } else {
                ForceGroupRespawn(object);
                QueueFieldObjectModeChange(object->world, work->groupIndex, TRUE);
                group->nextPose = 3;
                group->pose = group->nextPose;
                group->rowState = 0;
                group->isFinished = 1;
                group->isIdleLong = 0;
                group->isAnchored = 0;
                group->isRespawning = 1;
                work->moveDelta = zero;
                func_ov032_020bbc5c(group, work);
            }
        }
        work->isMoving = 0;
        work->isPushed = 0;
        break;
    }
    MoveGroupObjectAndSyncActor(object, &delta);
}


