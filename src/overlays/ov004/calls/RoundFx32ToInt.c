#include "nitro/types.h"
#include "nitro/fx_types.h"

int RoundFx32ToInt(fx32 value)
{
    return (int)(value + 0x800 + ((u32)(value + 0x800 >> 0xb) >> 0x14)) >> 0xc;
}
