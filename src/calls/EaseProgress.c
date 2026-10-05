#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern const s16 data_02053580[];

static inline fx32 MulFx32(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline fx32 SinRadians(fx32 radians)
{
    return data_02053580[(int)((((s64)radians << 16) / 0x6488) & 0xffff) >> 4];
}

fx32 EaseProgress(fx32 elapsed, fx32 duration, int mode)
{
    fx32 t = FX_Div(elapsed, duration);

    if (t >= 0x1000) {
        return 0x1000;
    }
    switch (mode) {
    case 0:
        break;
    case 1:
        return (SinRadians(MulFx32(t, 0x3244) - 0x1922) + 0x1000) / 2;
    case 2:
        return SinRadians(MulFx32(t, 0x1922) - 0x1922) + 0x1000;
    case 3:
        return SinRadians(MulFx32(t, 0x1922));
    }
    return t;
}
