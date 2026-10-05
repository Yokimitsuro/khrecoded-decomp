#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    s16 followLink;
    u8 pad_08[0x10];
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
    u8 pad_0E[0xC];
    s16 unk_1a;
    u8 pad_1C[0xC];
    u32 settleTimer;
    u8 pad_2C[0xC];
    s16 bounceCount;
} ObjectGroup;

typedef struct HitResult {
    u32 unk_00;
    u32 hitWall;
} HitResult;

extern const VecFx32 data_0205344c;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void ComputeGroupOrbitPosition(GroupObject *object, VecFx32 *target);
extern void ComputeGroupAimDelta(GroupObject *object, GroupObject *leader, VecFx32 *delta);
extern BOOL ComputePushTowardTarget(VecFx32 *target, VecFx32 *center, s32 *phase, VecFx32 *push);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL func_ov032_020bc770(VecFx32 *position, fx32 radius, VecFx32 *out);
extern void SpawnSoundSlot(int bank, int id, VecFx32 *position, int flags);
extern HitResult *func_ov032_020bcac4(VecFx32 *position, int mask, fx32 radius, VecFx32 *velocity, VecFx32 *delta);
extern void ResetGroupOrbitPhase(GroupObject *object);
extern BOOL TurnTowardOpenDirection(GroupObject *object, VecFx32 *position, fx32 radius);
extern void func_ov032_020bbca0(void *world, int groupIndex, int slotIndex, VecFx32 *out);
extern BOOL UpdateHopWithSpeedRamp(void *world, int groupIndex, GroupMemberWork *work, VecFx32 *position, VecFx32 *velocity, fx32 radius, VecFx32 *delta, BOOL *landed);
extern BOOL func_ov032_020bbf50(ObjectGroup *group);
extern void PickJitteredPlayerOffset(GroupObject *object, VecFx32 *offset);
extern void func_ov032_020bbce4(GroupObject *object, VecFx32 *delta);
extern void func_ov032_020bbd80(GroupObject *object, VecFx32 *delta);

void UpdateBouncingGroupMember(GroupObject *object)
{
    VecFx32 delta;
    VecFx32 target;
    VecFx32 next;
    VecFx32 landing;
    VecFx32 goal;
    VecFx32 zero;
    BOOL landed;
    void *world = object->world;
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);
    GroupObject *leader = NULL;
    GroupMemberWork *leaderWork = NULL;
    BOOL still;
    HitResult *hit;
    BOOL reached;

    zero = data_0205344c;
    delta = data_0205344c;
    if (work->followLink != -1) {
        leader = func_ov001_02086384(world, work->followLink);
        leaderWork = func_ov032_020bbc98(leader);
    }
    switch (work->state) {
    case 0:
        if (group->isAnchored) {
            work->state = 0x13;
        } else {
            work->state = 0x15;
            group->landSoundPlayed = 1;
        }
        break;
    case 0x13:
        target = *func_ov001_0206dc4c(0);
        ComputeGroupOrbitPosition(object, &target);
        if (leader == NULL) {
            if (ComputePushTowardTarget(&target, &object->position, &work->phase, &delta)) {
                func_01ff9e0c(&object->position, &delta, &next);
                if (func_ov032_020bc770(&next, 0xc00, &landing)) {
                    work->state = 0x14;
                    work->moveDelta.z = 0;
                    work->moveDelta.x = 0;
                    work->moveDelta.y = -0x596;
                    group->bounceCount++;
                    group->unk_1a = 0;
                    if (!group->cueSoundPlayed) {
                        SpawnSoundSlot(0xf8, 7, &object->position, 0);
                        group->cueSoundPlayed = 1;
                    }
                }
            }
        } else {
            work->moveDelta = leaderWork->moveDelta;
            work->state = leaderWork->state;
            ComputeGroupAimDelta(object, leader, &delta);
        }
        break;
    case 0x14:
        if (leader == NULL) {
            hit = func_ov032_020bcac4(&object->position, 7, 0xc00, &work->moveDelta, &delta);
            work->moveDelta.y -= 0x11e;
            if (hit != NULL && hit->hitWall != 0) {
                SpawnSoundSlot(0xf8, 6, &object->position, 0);
                if (group->bounceCount < 5) {
                    work->state = 0x13;
                } else {
                    work->moveDelta = zero;
                    work->state = 0x15;
                }
            }
        } else {
            work->state = leaderWork->state;
            ComputeGroupAimDelta(object, leader, &delta);
            if (work->leaderLink == -1 && work->state != 0x14) {
                ResetGroupOrbitPhase(object);
            }
        }
        break;
    case 0x15:
        if (leader == NULL) {
            if (TurnTowardOpenDirection(object, &object->position, 0xc00)) {
                func_ov032_020bbca0(object->world, work->groupIndex, work->slotIndex, &work->moveDelta);
                object->work->state = 0x16;
                group->isFalling = 1;
            }
        } else {
            ComputeGroupAimDelta(object, leader, &delta);
            work->state = leaderWork->state;
        }
        break;
    case 0x16:
        if (leader == NULL) {
            landed = FALSE;
            still = FALSE;
            if (work->moveDelta.x == 0 && work->moveDelta.z == 0) {
                still = TRUE;
            }
            reached = UpdateHopWithSpeedRamp(object->world, work->groupIndex, work, &object->position, &work->moveDelta,
                                          0xc00, &delta, &landed);
            if ((landed && !still) || (still && reached)) {
                object->work->state = 0x15;
            }
            if (reached && !group->landSoundPlayed) {
                SpawnSoundSlot(0xf8, 5, &object->position, 0);
                group->landSoundPlayed = 1;
            }
            if (func_ov032_020bbf50(group)) {
                PickJitteredPlayerOffset(object, &work->offset);
                work->phase = 0;
                work->state = 0x17;
                if (object->work->leaderLink == -1) {
                    group->settleTimer = 0;
                    group->isFalling = 0;
                    group->isAnchored = 1;
                    group->arrivedCount = 0;
                    SpawnSoundSlot(0xf8, 4, &object->position, 0);
                }
            }
        } else {
            ComputeGroupAimDelta(object, leader, &delta);
            work->state = leaderWork->state;
        }
        break;
    case 0x17:
        func_01ff9e0c(func_ov001_0206dc4c(0), &work->offset, &goal);
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
    func_ov032_020bbce4(object, &delta);
    delta.y = 0;
    func_ov032_020bbd80(object, &delta);
}
