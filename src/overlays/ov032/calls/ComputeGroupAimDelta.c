#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x38];
    VecFx32 position;
} GroupObject;

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern void *func_ov032_020bbc80(GroupObject *object);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);

void ComputeGroupAimDelta(GroupObject *object, GroupObject *target, VecFx32 *out)
{
    GroupMemberWork *work;
    GroupMemberWork *self;

    func_ov032_020bbc80(object);
    work = func_ov032_020bbc98(object);
    self = func_ov032_020bbc98(object);
    if (target != NULL) {
        VecFx32 aim = target->position;
        aim.y += 0x1800;
        func_01ff9e3c(&aim, &object->position, out);
        if (out->x != 0 || out->y != 0 || out->z != 0) {
            VEC_Mag(out);
            out->x = out->x * 0x55 / 100;
            out->y = out->y * 0x46 / 100;
            out->z = out->z * 0x55 / 100;
        }
        work->state = self->state;
    }
}
