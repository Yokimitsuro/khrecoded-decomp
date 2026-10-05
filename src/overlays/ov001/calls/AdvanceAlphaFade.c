#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AlphaFadeOwner {
    u8 pad_000[0x320];
    u8 alpha;
    u8 fromAlpha;
    u8 toAlpha;
    u8 pad_323;
    s32 elapsed;
    s32 duration;
} AlphaFadeOwner;

extern fx32 SafeFixedRatio(s32 numerator, s32 denominator);
extern fx32 FixedPointLerp(fx32 from, fx32 to, fx32 t);

void AdvanceAlphaFade(AlphaFadeOwner *owner, s32 step)
{
    s32 duration = owner->duration;
    fx32 t;

    if (duration == 0) {
        return;
    }
    owner->elapsed += step;
    if (owner->elapsed < 0) {
        return;
    }
    if (owner->elapsed >= duration) {
        owner->elapsed = duration;
    }
    t = SafeFixedRatio(owner->elapsed, owner->duration);
    owner->alpha = FixedPointLerp(owner->fromAlpha << 12, owner->toAlpha << 12, t) >> 12;
    if (owner->elapsed >= owner->duration) {
        owner->duration = 0;
    }
}
