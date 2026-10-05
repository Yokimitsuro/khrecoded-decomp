#include "nitro/types.h"
#include "nitro/fx.h"

extern u8 *data_0205fe0c;

fx32 CountUnlockedSlotsFx(void)
{
    fx32 total = FX32_ONE;
    u8 flags = data_0205fe0c[0x2c64];
    u16 bit;

    for (bit = 0; bit < 3; bit++) {
        total += ((flags >> bit) & 1) << 12;
    }
    return total;
}
