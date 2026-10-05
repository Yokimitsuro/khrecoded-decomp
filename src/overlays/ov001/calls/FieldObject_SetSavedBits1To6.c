#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x7e];
    u8 savedBits;
} FieldObject;

extern u16 FieldObject_GetSavedValue(FieldObject *object);
extern void func_ov001_0207f9f0(FieldObject *object, u16 value);

void FieldObject_SetSavedBits1To6(FieldObject *object, int bits)
{
    u32 value = FieldObject_GetSavedValue(object);

    object->savedBits = bits;
    func_ov001_0207f9f0(object, (bits << 1) | (value & ~0x7e));
}
