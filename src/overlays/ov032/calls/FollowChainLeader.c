#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x1E];
    VecFx32 moveDelta;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
    u8 pad_08[0x30];
    VecFx32 position;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
} ObjectGroup;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern void SampleGroupTrailPosition(void *context, GroupObject *object, VecFx32 *goal, u8 *blocked);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(const VecFx32 *v, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern BOOL SnapPositionToGround(VecFx32 *position, VecFx32 *velocity, VecFx32 *out, fx32 radius);
extern void func_ov032_020bbd80(GroupObject *object, VecFx32 *delta);

static inline VecFx32 ScaleToLength(VecFx32 vec, fx32 length)
{
    func_01ffaff4(&vec, &vec);
    ScaleVecFx32InPlace(&vec, length);
    return vec;
}

static inline VecFx32 AddVectors(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add(a, b, &sum);
    return sum;
}

void FollowChainLeader(void *context, GroupObject *object, int speed)
{
    VecFx32 delta;
    VecFx32 toLeader;
    VecFx32 target;
    VecFx32 goal;
    VecFx32 offset;
    VecFx32 next;
    u8 blocked;
    fx32 dist;
    BOOL near;
    fx32 limit;
    GroupObject *prev;
    VecFx32 *leaderPos;
    GroupMemberWork *work;
    ObjectGroup *group;

    work = func_ov032_020bbc98(object);
    group = func_ov032_020bbc80(object);
    goal = object->position;
    blocked = 0;
    near = FALSE;
    leaderPos = &func_ov001_02086384(object->world, group->leaderIndex)->position;
    if (work->leaderLink == -1) {
        prev = NULL;
    } else {
        prev = func_ov001_02086384(object->world, work->leaderLink);
    }
    SampleGroupTrailPosition(context, object, &goal, &blocked);
    VEC_Subtract(&object->position, leaderPos, &toLeader);
    VEC_Subtract(&object->position, &prev->position, &delta);
    if (VEC_Mag(&delta) < 0x1800) {
        near = TRUE;
    }
    if (delta.x != 0 || delta.y != 0 || delta.z != 0) {
        delta.y -= 200;
        offset = ScaleToLength(delta, 0x1800);
        VEC_Add(&prev->position, &offset, &target);
    } else {
        target = object->position;
        return;
    }
    VEC_Subtract(&target, &object->position, &delta);
    if (delta.x != 0 || delta.y != 0 || delta.z != 0) {
        if (speed != 0) {
            dist = VEC_Mag(&delta);
            if (near) {
                limit = speed / 8;
            } else {
                limit = speed * 25 / 10;
            }
            if (dist < limit) {
                limit = dist;
            }
            work->moveDelta = ScaleToLength(delta, limit);
        } else {
            work->moveDelta = delta;
        }
    } else {
        work->moveDelta = delta;
    }
    if (!blocked) {
        SnapPositionToGround(&object->position, &work->moveDelta, &work->moveDelta, 0x1800);
    }
    next = AddVectors(&object->position, &work->moveDelta);
    VEC_Subtract(&prev->position, &next, &delta);
    func_ov032_020bbd80(object, &delta);
}
