#include "nitro/types.h"

extern u16 SharedObject_GetField2(void *obj);
extern u16 AddQuantizedViewAngle(u16 angle);

u16 QuantizeFieldAngle(void *obj)
{
    return AddQuantizedViewAngle(SharedObject_GetField2(obj) + 0x3fff);
}
