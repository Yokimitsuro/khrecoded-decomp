#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_004[0x5c];
    u32 slotA;
    u32 slotB;
} ObjHandle;

void ResetObjHandle(ObjHandle *obj)
{
    obj->slotA = 0;
    obj->slotB = 0;
    obj->flags = obj->flags & 0xffffffc0;
}
