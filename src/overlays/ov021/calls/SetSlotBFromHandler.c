#include "nitro/types.h"

extern u32 GetObjHandleLevel(void);

typedef struct {
    u8 pad_000[0x64];
    u32 slotB;
} ObjHandle;

void SetSlotBFromHandler(ObjHandle *obj)
{
    obj->slotB = GetObjHandleLevel();
}
