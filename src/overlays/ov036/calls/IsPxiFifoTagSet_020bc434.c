#include "nitro/types.h"

extern u32 data_ov036_020c36e0;
extern u32 Obj_GetWord28(u32 tag);

BOOL IsPxiFifoTagSet_020bc434(void)
{
    u32 result;

    result = Obj_GetWord28(data_ov036_020c36e0);
    return result != 0;
}
