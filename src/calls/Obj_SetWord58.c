#include "nitro/types.h"

void Obj_SetWord58(u32 *obj, u32 value)
{
    obj[0x16] = value;
}
