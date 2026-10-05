#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Quaternion {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quaternion;

extern const s16 data_02053580[];

void QuatFromAxisAngle(Quaternion *out, const VecFx32 *axis, fx32 angle)
{
    int index;
    fx32 sine;

    index = (int)((unsigned)((int)(((s64)(angle >> 1) * 0x28be60db9391LL + 0x80000000000LL) >> 32) << 4) >> 16) >> 4;
    out->w = data_02053580[(0x400 - index) & 0xfff];
    sine = data_02053580[index];
    out->x = (fx32)(((s64)sine * axis->x + 0x800) >> 12);
    out->y = (fx32)(((s64)sine * axis->y + 0x800) >> 12);
    out->z = (fx32)(((s64)sine * axis->z + 0x800) >> 12);
}
