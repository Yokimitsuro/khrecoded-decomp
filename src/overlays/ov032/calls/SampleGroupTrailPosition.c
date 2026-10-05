#include "nitro/types.h"
#include "nitro/fx_types.h"

#define TRAIL_WRAP(i) ((((i) < 0) ? (i) + 0x1f : (i)) % 0x20)

typedef struct ObjectGroup {
    u8 pad_00[0x38];
    VecFx32 trail[32];
    u8 trailFlags[32];
    int trailHead;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(void *object);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void SampleGroupTrailPosition(int slot, void *object, VecFx32 *out, u8 *outFlag)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    int i = group->trailHead - 1;
    fx32 total = 0;
    fx32 spacing = slot * 0x1800;
    int end;
    int prev;
    int cur;
    VecFx32 diff;
    VecFx32 dir;

    *outFlag = 0;
    end = i;
    end -= 0x20;
    for (; i > end && i > 0; i--) {
        cur = TRAIL_WRAP(i);
        prev = TRAIL_WRAP(i - 1);
        VEC_Subtract(&group->trail[cur], &group->trail[prev], &diff);
        total += VEC_Mag(&diff);
        if (total >= spacing) {
            VEC_Normalize(&diff, &dir);
            ScaleVecFx32InPlace(&dir, total - spacing);
            VEC_Add(&group->trail[prev], &dir, out);
            *outFlag = group->trailFlags[cur];
            return;
        }
    }
}
