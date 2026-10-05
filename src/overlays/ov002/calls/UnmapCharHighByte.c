#include "nitro/types.h"

extern u8 data_ov002_0206ad7c[];

u16 UnmapCharHighByte(int code)
{
    u8 high = (code & 0xff00) >> 8;
    u8 index;
    for (index = 0; index < 13; index++) {
        if (high == data_ov002_0206ad7c[index]) {
            return (code & 0xff) | (index << 8);
        }
    }
    return 0;
}
