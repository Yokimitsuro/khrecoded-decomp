#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u8 *data_0205fe0c;

fx32 GetDifficultyScale(void)
{
    u16 level = data_0205fe0c[0x2c66] & 7;

    switch (level) {
    case 2:
        level = 3;
        break;
    case 3:
        level = 2;
        break;
    case 4:
        level = 4;
        break;
    case 5:
        level = 5;
        break;
    case 0:
    case 1:
        break;
    }
    return level << 12;
}
