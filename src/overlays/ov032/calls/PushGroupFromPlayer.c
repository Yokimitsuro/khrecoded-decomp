#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    u8 pad_00[0x30];
    s32 phase;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x38];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
} ObjectGroup;

extern const VecFx32 data_0205344c;

extern GroupMemberWork *func_ov032_020bbc98(void *object);
extern ObjectGroup *func_ov032_020bbc80(void *object);
extern void *func_ov001_0206dc4c(int index);
extern BOOL ComputePushTowardTarget(void *target, VecFx32 *center, s32 *phase, VecFx32 *push);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL ProbeGroundBelow(VecFx32 *position, fx32 radius, VecFx32 *out);

BOOL PushGroupFromPlayer(void *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    GroupMemberWork *work = func_ov032_020bbc98(object);
    VecFx32 zero = data_0205344c;
    VecFx32 probe;
    VecFx32 push = zero;
    BOOL grounded = FALSE;

    ComputePushTowardTarget(func_ov001_0206dc4c(0), &group->center, &work->phase, &push);
    group->velocity = zero;
    VEC_Add(&group->center, &push, &group->center);
    probe.x = group->center.x;
    probe.y = group->center.y - 0x1b33;
    probe.z = group->center.z;
    if (ProbeGroundBelow(&probe, 0x1b33, &push)) {
        grounded = TRUE;
    }
    return grounded;
}
