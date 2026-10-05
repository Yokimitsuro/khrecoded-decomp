#include "nitro/types.h"

void SetBit1WhenBit0Set(u32 *flags, s32 enable)
{
    u32 value = *flags;

    if ((value & 1) != 0) {
        if (enable != 0) {
            *flags = value | 2;
            return;
        }
        *flags = value & 0xfffffffd;
    }
}
