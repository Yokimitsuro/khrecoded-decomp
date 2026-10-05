#include "nitro/types.h"
#include "nitro/fx_types.h"

extern s64 _ll_sdiv(s64 numerator, s64 denominator);
extern const s16 data_02053580[];

static inline int RadiansToIndex(fx32 radians)
{
    return (int)(_ll_sdiv((s64)radians << 16, 0x6488) & 0xffff) >> 4;
}

void DirectionFromYawPitch(fx32 yaw, fx32 pitch, VecFx32 *out)
{
    int pitchIndex = RadiansToIndex(pitch);
    int yawIndex;
    fx32 cosPitch;
    fx32 cosYaw;
    fx32 sinYaw;
    fx32 sinPitch;

    yaw = RadiansToIndex(yaw);
    yawIndex = yaw;
    cosPitch = data_02053580[(0x400 - pitchIndex) & 0xfff];
    cosYaw = data_02053580[(0x400 - yawIndex) & 0xfff];
    sinYaw = data_02053580[yawIndex];
    sinPitch = data_02053580[pitchIndex];

    out->x = (fx32)(((fx64)cosYaw * cosPitch + 0x800) >> 12);
    out->z = (fx32)(((fx64)sinYaw * cosPitch + 0x800) >> 12);
    out->y = sinPitch;
}
