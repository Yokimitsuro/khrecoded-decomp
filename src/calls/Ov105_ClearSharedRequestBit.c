#include "nitro/types.h"

extern u16 data_02ffff96;

void Ov105_ClearSharedRequestBit(void)
{
    u16 *flags = &data_02ffff96;

    if (*flags & 1) {
        *flags = *flags & 0xfffe;
    }
}
