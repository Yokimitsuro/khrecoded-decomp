#include "nitro/types.h"

typedef struct FieldObject FieldObject;

extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void FieldObject_SetSavedValue(FieldObject *object, u32 value);

void SetSavedValueFlag7(FieldObject *object, int flag)
{
    u32 value = FieldObject_GetSavedValue(object);

    FieldObject_SetSavedValue(object, (u16)((flag << 7) | (value & ~0x80)));
}
