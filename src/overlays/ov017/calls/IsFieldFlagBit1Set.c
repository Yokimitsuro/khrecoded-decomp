#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x4b];
    u8 flags : 7;
} FieldObject;

u32 IsFieldFlagBit1Set(FieldObject *object)
{
    return object->flags & 2;
}
