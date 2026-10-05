#include "nitro/types.h"
#include "nitro/fx_types.h"

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

extern void *func_ov032_020bbc98(GroupObject *object);
extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u32 random_next_scaled(u32 upperBound);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_01ffaff4(VecFx32 *in, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);

void PickJitteredLeaderOffset(GroupObject *object, VecFx32 *out)
{
    VecFx32 diff;
    u32 range;
    ObjectGroup *group;

    func_ov032_020bbc98(object);
    group = func_ov032_020bbc80(object);
    func_01ff9e3c(&func_ov001_02086384(object->world, group->leaderIndex)->position, &object->position, &diff);
    range = 0x3666;
    diff.x += random_next_scaled(range) - (range >> 1);
    diff.z += random_next_scaled(range) - (range >> 1);
    if (VEC_Mag(&diff) > (fx32)(range >> 1)) {
        VecFx32 dir = diff;
        func_01ffaff4(&dir, &dir);
        ScaleVecFx32InPlace(&dir, range >> 1);
        *out = dir;
    } else {
        *out = diff;
    }
}
