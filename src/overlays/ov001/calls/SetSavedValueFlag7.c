#include "nitro/types.h"

typedef struct FieldObject FieldObject;

extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void func_ov001_0207f9f0(FieldObject *object, u32 value);

void SetSavedValueFlag7(FieldObject *object, int flag)
{
    u32 value = FieldObject_GetSavedValue(object);

    func_ov001_0207f9f0(object, (u16)((flag << 7) | (value & ~0x80)));
}
