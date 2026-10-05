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
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x5];
    VecFx32 position;
    u8 pad_44[0xA8];
    GroupMemberWork *work;
} GroupObject;

typedef struct ObjectGroup {
    u8 pad_00[0x24];
    u32 approachTimer;
    u8 pad_28[0x10];
    VecFx32 memberOffsets[20];
    VecFx32 center;
} ObjectGroup;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern void *ActorRegistry_GetEntityByIndex(int actorId);
extern int GetRemainingRowSpan(GroupObject *object);
extern int ClampSymmetricValue(int value, int limit);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

BOOL SteerMemberToFormationSlot(GroupObject *object, u32 *step)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);
    BOOL done;
    fx32 speed;
    u32 remaining;
    VecFx32 target;
    VecFx32 dir;
    VecFx32 diff;
    VecFx32 next;
    VecFx32 offset;
    VecFx32 scaled;
    int limit;
    int dist;

    ActorRegistry_GetEntityByIndex(object->actorId);
    target = group->memberOffsets[GetRemainingRowSpan(object)];
    done = group->approachTimer >= 90 ? TRUE : FALSE;
    VEC_Add(&target, &group->center, &target);
    if (object->work->leaderLink == -1 && !done) {
        (*step)++;
    }
    remaining = 90 - *step;
    limit = remaining * 205 / 90;
    speed = remaining * 0xccd / 90;
    if (limit == 0) {
        limit = 1;
    }
    if (speed == 0) {
        speed = 1;
    }
    VEC_Subtract(&target, &object->position, &diff);
    work->moveDelta.x += ClampSymmetricValue(diff.x, limit);
    work->moveDelta.y += ClampSymmetricValue(diff.y, limit);
    work->moveDelta.z += ClampSymmetricValue(diff.z, limit);
    if (VEC_Mag(&work->moveDelta) > 0) {
        VEC_Normalize(&work->moveDelta, &work->moveDelta);
        ScaleVecFx32InPlace(&work->moveDelta, speed);
    }
    VEC_Add(&object->position, &work->moveDelta, &next);
    VEC_Subtract(&target, &next, &diff);
    dist = VEC_Mag(&diff) * *step / 90;
    if (dist > 0) {
        VEC_Normalize(&diff, &dir);
        scaled = dir;
        ScaleVecFx32InPlace(&scaled, dist);
        offset = scaled;
        VEC_Add(&work->moveDelta, &offset, &work->moveDelta);
    }
    return done;
}
