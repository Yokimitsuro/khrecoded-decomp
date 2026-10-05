#include "nitro/types.h"

typedef struct {
    u32 flags;
    u8 pad_004[0x5c];
    u32 slotA;
} ObjHandle;

BOOL HasSlotAAndBit2Set(ObjHandle *obj)
{
    if ((obj->slotA != 0) && ((obj->flags & 4) != 0)) {
        return TRUE;
    }
    return FALSE;
}
