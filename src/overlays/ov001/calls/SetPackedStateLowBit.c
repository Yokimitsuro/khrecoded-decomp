#include "nitro/types.h"

extern u16 FieldObject_GetSavedValue(void *object);
extern void func_ov001_0207f9f0(void *object, u16 state);

void SetPackedStateLowBit(void *object, u16 lowBit)
{
    u16 state = FieldObject_GetSavedValue(object);
    func_ov001_0207f9f0(object, lowBit | (state & ~1));
}
