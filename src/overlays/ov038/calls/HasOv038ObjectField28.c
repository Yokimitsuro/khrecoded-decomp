#include "nitro/types.h"

extern u32 data_ov038_020bbda0;
extern s32 Obj_GetWord28(u32 handle);

BOOL HasOv038ObjectField28(void)
{
    s32 result;

    result = Obj_GetWord28(data_ov038_020bbda0);
    return result != 0;
}
