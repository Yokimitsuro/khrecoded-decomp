#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x1E];
    VecFx32 moveDelta;
    s32 unk_30;
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
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 16;
    u32 memberTotal : 8;
    u32 arrivedCount : 8;
    u32 isFinished : 1;
    u32 unk_08_1 : 2;
    u32 isFalling : 1;
    u32 isAnchored : 1;
    u32 unk_08_5 : 27;
    u16 memberCount : 8;
    u16 unk_0C_8 : 2;
    u16 cueSoundPlayed : 1;
    u16 unk_0C_11 : 5;
    u8 pad_0E[0x1A];
    u32 settleTimer;
    u8 pad_2C[0xC];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern void InitGroupFormation(GroupObject *object);
extern void SpawnSoundSlot(int bank, int soundId, VecFx32 *position, int flags);
extern void AdvanceGroupSettleCounter(GroupObject *object);
extern BOOL PushGroupFromPlayer(GroupObject *object);
extern int GetRemainingRowSpan(GroupObject *object);
extern VecFx32 StepTowardGroundTarget(GroupObject *object, ObjectGroup *group, GroupMemberWork *work, VecFx32 *offset, VecFx32 *position);
extern BOOL SnapPositionToGround(VecFx32 *position, VecFx32 *velocity, VecFx32 *out, fx32 radius);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SteerMemberToFormationSlot(GroupObject *object, s32 *mask);
extern BOOL TurnTowardOpenDirection(GroupObject *object, VecFx32 *position, fx32 radius);
extern void func_ov032_020bbca0(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL UpdateHopWithSpeedRamp(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern BOOL HasPendingNibbleChange(ObjectGroup *group);
extern void *func_ov001_0206dc4c(int index);
extern BOOL ComputePushTowardTarget(void *target, VecFx32 *center, s32 *phase, VecFx32 *push);
extern void RollGroupAndSteerMember(GroupObject *object, const VecFx32 *delta);
extern void MoveGroupObjectAndSyncActor(GroupObject *object, VecFx32 *delta);

int UpdateGroupMember(GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);
    VecFx32 position = group->center;
    GroupObject *leader = func_ov001_02086384(object->world, group->leaderIndex);

    if (object->work->leaderLink == -1) {
        position.y -= 0x1b33;
    }
    switch (work->state) {
    case 0:
        if (object->work->leaderLink == -1) {
            InitGroupFormation(object);
        }
        if (group->isAnchored) {
            object->work->state = 8;
        } else {
            object->work->state = 10;
        }
        break;
    case 8:
        if (group->arrivedCount == group->memberTotal) {
            object->work->state = 9;
            work->moveDelta = data_0205344c;
            if (!group->cueSoundPlayed) {
                SpawnSoundSlot(0xf8, 7, &object->position, 0);
                group->cueSoundPlayed = 1;
            }
        } else if (work->leaderLink == -1) {
            if (group->arrivedCount != group->memberTotal) {
                AdvanceGroupSettleCounter(object);
            }
            if (PushGroupFromPlayer(object)) {
                work->moveDelta = group->velocity;
                group->arrivedCount = 1;
            } else {
                work->moveDelta = group->velocity;
            }
        } else {
            VecFx32 offset = group->memberOffsets[GetRemainingRowSpan(object)];
            work->moveDelta = StepTowardGroundTarget(object, group, work, &offset, &object->position);
        }
        break;
    case 9:
        if (object->work->leaderLink == -1) {
            group->velocity.z = 0;
            group->velocity.x = 0;
            group->velocity.y -= 0x1ad;
            if (SnapPositionToGround(&position, &group->velocity, &group->velocity, 0x1b33)) {
                object->work->state = 10;
                SpawnSoundSlot(0xf8, 5, &object->position, 0);
            }
            VEC_Add(&group->center, &group->velocity, &group->center);
        } else {
            object->work->state = leader->work->state;
        }
        {
            s32 mask = 0x3f;
            SteerMemberToFormationSlot(object, &mask);
        }
        break;
    case 10:
        if (object->work->leaderLink == -1) {
            group->isFalling = 1;
            group->isAnchored = 0;
            if (TurnTowardOpenDirection(object, &position, 0x1b33)) {
                func_ov032_020bbca0(object->world, work->groupIndex, work->slotIndex, &group->velocity);
                object->work->state = 11;
            }
        } else {
            object->work->state = 11;
        }
        RollGroupAndSteerMember(object, &data_0205344c);
        break;
    case 11:
        if (object->work->leaderLink == -1) {
            BOOL landed = 0;
            VecFx32 delta = data_0205344c;
            BOOL reached = UpdateHopWithSpeedRamp(object->world, work->groupIndex, work, &position, &group->velocity, 0x1b33, &delta, &landed);

            if (landed) {
                object->work->state = 10;
            }
            VEC_Add(&group->center, &delta, &group->center);
            if (reached) {
                if (HasPendingNibbleChange(group)) {
                    object->work->state = 12;
                    group->isFalling = 0;
                    group->settleTimer = 0;
                    group->isAnchored = 1;
                    work->unk_30 = 0;
                    SpawnSoundSlot(0xf8, 4, &object->position, 0);
                }
            } else if (group->center.y < 0) {
                work->state = 8;
            }
            RollGroupAndSteerMember(object, &delta);
        } else {
            object->work->state = leader->work->state;
            RollGroupAndSteerMember(object, &data_0205344c);
        }
        break;
    case 12:
        if (object->work->leaderLink == -1) {
            if (group->settleTimer < 4) {
                VecFx32 push;
                if (ComputePushTowardTarget(func_ov001_0206dc4c(0), &group->center, &work->unk_30, &push)) {
                    group->settleTimer += 0x89;
                }
                group->velocity = data_0205344c;
                VEC_Add(&group->center, &push, &group->center);
            } else {
                group->isFinished = 1;
            }
        }
        RollGroupAndSteerMember(object, &data_0205344c);
        break;
    }
    MoveGroupObjectAndSyncActor(object, &work->moveDelta);
    return 0;
}
