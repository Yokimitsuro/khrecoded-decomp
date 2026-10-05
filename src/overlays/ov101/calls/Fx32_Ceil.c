#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

fx32 Fx32_Ceil(fx32 value)
{
    if ((value & (FX32_ONE - 1)) != 0) {
        value = (value & ~(FX32_ONE - 1)) + FX32_ONE;
    }
    return value;
}
