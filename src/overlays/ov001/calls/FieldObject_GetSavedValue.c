#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);

u16 FieldObject_GetSavedValue(FieldObject *object)
{
    u32 saved = ReadSessionPackedBits(object->saveBitOffset, object->saveBitCount);

    return (u16)((saved & 0xfffe) >> 1);
}
