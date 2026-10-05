#include "nitro/types.h"
#include "nitro/fx_types.h"

extern fx32 GetGlobalScaleValue(void);
extern fx32 FX_Mul(fx32 a, fx32 b);

void ApplyActorScaleFactors(u8 *actor)
{
    fx32 value;

    value = GetGlobalScaleValue();
    value = FX_Mul(value, *(fx32 *)(actor + 0x39c));
    FX_Mul(value, *(fx32 *)(actor + 0x3a0));
}
