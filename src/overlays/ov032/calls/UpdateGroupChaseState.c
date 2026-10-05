#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x12];
    VecFx32 targetOffset;
    u8 pad_24[0xc];
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
    u32 unk_00_23 : 9;
    u32 unk_04;
    u32 isFinished : 1;
    u32 unk_08_1 : 1;
    u32 isIdleLong : 1;
    u32 isFalling : 1;
    u32 isAnchored : 1;
    u32 unk_08_5 : 27;
    u16 memberCount : 8;
    u16 isChasing : 1;
    u16 unk_0c_9 : 7;
    u8 pad_0e[4];
    u16 chaseLimit;
    u8 pad_14[0x14];
    u32 settleTimer;
    u8 pad_2c[0xc];
    s16 idleTime;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern s32 func_ov032_020bbc2c(void *world, int groupIndex);
extern void PickJitteredPlayerOffset(GroupObject *object, VecFx32 *out);
extern void func_ov032_020bd268(GroupObject *object);
extern void SpawnSoundSlot(int bank, int soundId, VecFx32 *position, int flags);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ComputePushTowardTarget(const VecFx32 *target, const VecFx32 *center, fx32 *speed, VecFx32 *push);
extern void func_ov032_020bbf68(void *world, int groupIndex);
extern void func_ov032_020bbce4(GroupObject *object, const VecFx32 *delta);

void UpdateGroupChaseState(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);
    VecFx32 delta;
    VecFx32 target;

    func_ov001_02086384(object->world, group->leaderIndex);
    delta = data_0205344c;
    switch (work->state) {
    case 0:
        work->state = 0x1b;
        break;
    case 0x1b:
        if (work->leaderLink == -1) {
            if (group->idleTime < 300) {
                group->idleTime++;
                if (group->idleTime >= 300) {
                    group->isIdleLong = 0;
                    group->chaseLimit = func_ov032_020bbc2c(object->world, work->groupIndex);
                }
            } else {
                group->isIdleLong = 1;
            }
        }
        if (group->pose == 3) {
            work->state = 0x1c;
            PickJitteredPlayerOffset(object, &work->targetOffset);
            work->phase = 0;
            if (object->work->leaderLink == -1) {
                group->settleTimer = 0;
                group->isFalling = 0;
                group->isAnchored = 1;
                group->isChasing = 1;
                func_ov032_020bd268(object);
                SpawnSoundSlot(0xf8, 4, &object->position, 0);
            }
        }
        break;
    case 0x1c: {
        BOOL reached;
        VEC_Add(func_ov001_0206dc4c(0), &work->targetOffset, &target);
        reached = ComputePushTowardTarget(&target, &object->position, &work->phase, &delta);
        if (object->work->leaderLink == -1) {
            if (group->settleTimer < 4) {
                if (reached) {
                    group->settleTimer += 0x89;
                }
            } else {
                func_ov032_020bbf68(object->world, work->groupIndex);
                group->isFinished = 1;
                group->isIdleLong = 0;
            }
        }
        break;
    }
    }
    func_ov032_020bbce4(object, &delta);
}
