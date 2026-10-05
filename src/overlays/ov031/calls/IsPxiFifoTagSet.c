#include "nitro/types.h"

extern u32 data_ov031_020bc7a0;
extern u32 Obj_GetWord28(u32 tag);

u32 IsPxiFifoTagSet(void)
{
    u32 result;

    result = Obj_GetWord28(data_ov031_020bc7a0);
    if (result != 0) {
        return 1;
    }
    return 0;
}
