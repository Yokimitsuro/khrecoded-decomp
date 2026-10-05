#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int _s32_div_f(int numerator, int denominator);
extern int nextRandom12(void);
extern unsigned int random_next_scaled(unsigned int upperBound);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern const VecFx32 data_0205344c;
extern const s16 data_02053580[];

void ComputeFormationPosition(const VecFx32 *origin, u32 pattern, fx32 spacing, int index, int count, VecFx32 *out)
{
    VecFx32 offset;

    *out = *origin;
    if (pattern >= 2 && pattern <= 4) {
        int step;

        offset = data_0205344c;
        if (count <= 1) {
            return;
        }
        step = _s32_div_f(spacing * 2, count - 1);
        switch (pattern) {
        case 2:
            offset.x = step * index - spacing;
            break;
        case 3:
            offset.y = spacing - step * index;
            break;
        case 4:
            offset.z = step * index - spacing;
            break;
        }
        VEC_Add(&offset, origin, out);
    } else if (pattern == 1 || pattern == 6) {
        int randomScale = nextRandom12();
        int angle = (int)random_next_scaled(0x10000) >> 4;
        fx32 radius = (fx32)(((s64)randomScale * spacing + 0x800) >> 12);

        offset.x = data_02053580[angle];
        offset.y = 0;
        offset.z = data_02053580[(0x400 - angle) & 0xfff];
        VEC_MultAdd(radius, &offset, origin, out);
    } else if (pattern == 5) {
        int angleStep = _s32_div_f(0xffff, count);
        int angle = (angleStep * index) >> 4;

        offset.x = data_02053580[(0x400 - angle) & 0xfff];
        offset.y = 0;
        offset.z = data_02053580[angle];
        VEC_MultAdd(spacing, &offset, origin, out);
    }
}
