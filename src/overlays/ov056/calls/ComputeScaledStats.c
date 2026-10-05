#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 primary;
    s32 secondary;
    u8 pad_08[4];
    s32 tertiary;
    u8 isValid;
} ScaledStats;

typedef struct {
    u8 pad_000[0x178];
    s32 basePrimary;
    s32 baseSecondary;
    s32 baseTertiary;
} StatSource;

extern s32 FX_Mul(s32 left, s32 right);
extern s32 _s32_div_f(s32 numerator, s32 denominator);

void ComputeScaledStats(StatSource *source, ScaledStats *stats, s32 percent, u8 flags, fx32 scale)
{
    s32 primary;
    s32 tertiary;
    s32 secondary;

    stats->isValid = TRUE;
    primary = source->basePrimary;
    stats->primary = primary;
    stats->primary += _s32_div_f(FX_Mul(scale, primary * percent), 100);
    tertiary = source->baseTertiary;
    stats->tertiary = tertiary + _s32_div_f(tertiary * percent, 100);
    secondary = source->baseSecondary;
    stats->secondary = secondary;
    if (flags & 1) {
        stats->secondary += _s32_div_f(secondary * percent, 100);
    }
}
