#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 followLink;
    u32 unk_08_0 : 4;
    u32 side : 1;
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
    u16 unk_0C_8 : 1;
    u16 landSoundPlayed : 1;
    u16 cueSoundPlayed : 1;
    u16 unk_0C_11 : 5;
    u8 pad_0E[0x1A];
    u32 settleTimer;
    u8 pad_2C[0x1AC];
    int trailSlot;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ComputePushTowardTarget(const VecFx32 *target, const VecFx32 *center, s32 *phase, VecFx32 *push);
extern void SpawnSoundSlot(int bank, int id, VecFx32 *position, int flags);
extern void AdvanceGroupSettleCounter(GroupObject *object);
extern void StepTowardGroundTarget(VecFx32 *out, GroupObject *object, ObjectGroup *group, GroupMemberWork *work, VecFx32 *offset, VecFx32 *position);
extern BOOL TurnTowardOpenDirection(GroupObject *object, VecFx32 *position, fx32 radius);
extern void func_ov032_020bbca0(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL UpdateHopWithSpeedRamp(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern BOOL HasPendingNibbleChange(ObjectGroup *group);
extern void SetGroupEntrySlotByte(GroupObject *object, u8 value, int slot);
extern int StoreGroupEntryVector(GroupObject *object, VecFx32 *position, int slot);
extern int GetRowMoveSpeed(void *world, int groupIndex);
extern void FollowChainLeader(void *context, GroupObject *object, int speed);
extern void PickJitteredLeaderOffset(GroupObject *object, VecFx32 *out);
extern void MoveGroupObjectAndSyncActor(GroupObject *object, const VecFx32 *delta);
extern void func_ov032_020bbd80(GroupObject *object, const VecFx32 *delta);

int UpdateChainGroupMember(void *context, GroupObject *object)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupObject *leader;
    VecFx32 zero;
    VecFx32 delta;
    VecFx32 goal;
    BOOL landed;
    u32 oldSide;
    BOOL reached;

    zero = data_0205344c;
    delta = data_0205344c;
    if (work->leaderLink == -1) {
        leader = NULL;
    } else {
        leader = func_ov001_02086384(object->world, work->leaderLink);
    }
    switch (work->state) {
    case 0:
        if (group->isAnchored) {
            object->work->state = 1;
        } else {
            object->work->state = 3;
            group->landSoundPlayed = 1;
        }
        if (object->work->leaderLink == -1) {
            SetGroupEntrySlotByte(object, 0, group->trailSlot);
            group->trailSlot = StoreGroupEntryVector(object, &object->position, group->trailSlot);
        }
        break;
    case 1:
        if (group->arrivedCount == group->memberTotal) {
            object->work->state = 2;
            if (!group->cueSoundPlayed) {
                SpawnSoundSlot(0xf8, 7, &object->position, 0);
                group->cueSoundPlayed = 1;
            }
        } else {
            if (work->leaderLink == -1 && group->arrivedCount != group->memberTotal) {
                AdvanceGroupSettleCounter(object);
            }
            StepTowardGroundTarget(&delta, object, group, work, &work->offset, &object->position);
        }
        break;
    case 2:
        if (work->leaderLink == -1) {
            work->moveDelta = zero;
            work->moveDelta.y = -0x11e;
            SetGroupEntrySlotByte(object, work->side, group->trailSlot);
            group->trailSlot = StoreGroupEntryVector(object, &object->position, group->trailSlot);
            group->isAnchored = 0;
        }
        object->work->state = 4;
        break;
    case 3:
        if (object->work->leaderLink == -1) {
            group->isFalling = 1;
            if (TurnTowardOpenDirection(object, &object->position, 0xc00)) {
                func_ov032_020bbca0(object->world, work->groupIndex, work->slotIndex, &work->moveDelta);
                SetGroupEntrySlotByte(object, work->side, group->trailSlot);
                group->trailSlot = StoreGroupEntryVector(object, &object->position, group->trailSlot);
                object->work->state = 4;
            }
        } else {
            object->work->state = 4;
        }
        break;
    case 4:
        if (object->work->leaderLink == -1) {
            landed = FALSE;
            oldSide = work->side;
            reached = UpdateHopWithSpeedRamp(object->world, work->groupIndex, work, &object->position, &work->moveDelta, 0xc00, &delta, &landed);
            if (oldSide != work->side) {
                SetGroupEntrySlotByte(object, work->side, group->trailSlot);
                group->trailSlot = StoreGroupEntryVector(object, &object->position, group->trailSlot);
            }
            if (reached && !group->landSoundPlayed) {
                SpawnSoundSlot(0xf8, 5, &object->position, 0);
                group->landSoundPlayed = 1;
            }
            if (landed) {
                object->work->state = 3;
            }
            if (reached && HasPendingNibbleChange(group)) {
                group->isFalling = 0;
                group->isAnchored = 1;
                work->state = 5;
                SpawnSoundSlot(0xf8, 4, &object->position, 0);
            }
            break;
        }
        FollowChainLeader(context, object, GetRowMoveSpeed(object->world, work->groupIndex));
        object->work->state = leader->work->state;
        delta = work->moveDelta;
        break;
    case 5:
        if (object->work->leaderLink == -1) {
            group->settleTimer = 0;
            work->state = 6;
        } else {
            object->work->state = leader->work->state;
        }
        if (work->state == 6) {
            PickJitteredLeaderOffset(object, &work->offset);
            work->phase = 0;
        }
        delta = work->moveDelta;
        break;
    case 6:
        VEC_Add(func_ov001_0206dc4c(0), &work->offset, &goal);
        reached = ComputePushTowardTarget(&goal, &object->position, &work->phase, &delta);
        if (object->work->leaderLink == -1) {
            if (group->settleTimer < 4) {
                if (reached) {
                    group->settleTimer += 0x89;
                }
            } else {
                group->isFinished = 1;
            }
        }
        break;
    }
    MoveGroupObjectAndSyncActor(object, &delta);
    if (object->work->leaderLink == -1) {
        StoreGroupEntryVector(object, &object->position, group->trailSlot - 1);
        func_ov032_020bbd80(object, &delta);
    }
    return 0;
}

