#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quaternion;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x1E];
    VecFx32 moveDelta;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x38];
    VecFx32 position;
} GroupObject;

typedef struct ObjectGroup {
    u8 pad_00[0x38];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
    Quaternion orientation;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern int func_ov032_020bc6f8(GroupObject *object);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_ov032_020bd1bc(Quaternion *out, const VecFx32 *axis, int angle);
extern void MultiplyFixedPointQuaternions(Quaternion *result, const Quaternion *left, const Quaternion *right);
extern void QuaternionToRotationMatrix(MtxFx33 *matrix, const Quaternion *quat);
extern void func_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline BOOL IsZeroVec(const VecFx32 *v)
{
    return v->x == 0 && v->y == 0 && v->z == 0;
}

void RollGroupAndSteerMember(GroupObject *object, const VecFx32 *delta)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);
    int slot = func_ov032_020bc6f8(object);
    int angle = 0;
    MtxFx33 rotation;
    Quaternion spin;
    VecFx32 target;
    VecFx32 diff;
    int rolled;

    if (work->leaderLink == -1) {
        rolled = VEC_Mag(delta) % 0xaad0;
        if (rolled > 0) {
            angle = (u16)((rolled << 16) / 0xaad0);
        }
        func_ov032_020bd1bc(&spin, &group->velocity, angle);
        MultiplyFixedPointQuaternions(&group->orientation, &spin, &group->orientation);
    }
    QuaternionToRotationMatrix(&rotation, &group->orientation);
    func_01ff9404(&group->memberOffsets[slot], &rotation, &target);
    VEC_Add(&target, &group->center, &target);
    VEC_Subtract(&target, &object->position, &diff);
    if (!IsZeroVec(&diff)) {
        work->moveDelta.x = diff.x * 17 / 100;
        work->moveDelta.z = diff.z * 17 / 100;
        work->moveDelta.y = diff.y * 80 / 100;
    } else {
        work->moveDelta = data_0205344c;
    }
}
