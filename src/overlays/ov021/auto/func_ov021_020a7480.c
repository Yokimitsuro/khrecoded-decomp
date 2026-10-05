#include "nitro/types.h"

void func_ov021_020a7480(void *object, u8 value)
{
    u8 *bytes = object;
    bytes[0x14] = value;
    bytes[0x17] = 0;
    bytes[6] = 0;
}
