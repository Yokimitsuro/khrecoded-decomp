#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_00[0x50];
    u16 id;
    u8 kind;
} FieldObject;

extern u32 ReadSessionPackedBits(u16 id, u8 kind);

BOOL IsObjectFlagClear(FieldObject *object)
{
    return (ReadSessionPackedBits(object->id, object->kind) & 1) == 0;
}
