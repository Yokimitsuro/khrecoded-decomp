#include "nitro/types.h"

extern u32 Obj_GetWord28();
extern u32 data_ov029_020bab80;

BOOL HasOv029ObjectField28(void)
{
    u32 value;

    value = Obj_GetWord28(data_ov029_020bab80);
    return value != 0;
}
