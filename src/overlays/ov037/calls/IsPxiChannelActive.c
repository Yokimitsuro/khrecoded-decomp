#include "nitro/types.h"

extern u32 data_ov037_020bb6c0;
extern s32 Obj_GetWord28(u32 handle);

BOOL IsPxiChannelActive(void)
{
    s32 result;

    result = Obj_GetWord28(data_ov037_020bb6c0);
    return result != 0;
}
