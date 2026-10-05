#include "nitro/types.h"

extern u8 data_ov002_0206ad7c[];

u16 RemapCharHighByte(int code)
{
    u8 high = (code & 0xff00) >> 8;
    return (code & 0xff) | (data_ov002_0206ad7c[high] << 8);
}
