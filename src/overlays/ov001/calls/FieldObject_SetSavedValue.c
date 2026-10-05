#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    u16 saveBitOffset;
    u8 saveBitCount;
} FieldObject;

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void FieldObject_SetSavedValue(FieldObject *object, u32 value)
{
    u32 saved = ReadSessionPackedBits(object->saveBitOffset, object->saveBitCount);

    WriteSessionPackedBits(object->saveBitOffset, object->saveBitCount,
                                    (value << 1) | (saved & 0xffff0001));
}
