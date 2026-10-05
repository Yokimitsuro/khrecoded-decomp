#include "nitro/types.h"

extern u16 FieldObject_GetSavedValue(void *object);
extern void FieldObject_SetSavedValue(void *object, u16 state);

void SetPackedStateLowBit(void *object, u16 lowBit)
{
    u16 state = FieldObject_GetSavedValue(object);
    FieldObject_SetSavedValue(object, lowBit | (state & ~1));
}
