#include "nitro/types.h"
#include "nitro/fx_types.h"

fx32 CeilFx32(fx32 value)
{
    if (value & 0xfff) {
        value = (value & ~0xfff) + 0x1000;
    }
    return value;
}
