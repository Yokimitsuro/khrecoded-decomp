#include "nitro/types.h"

extern u32 Obj_SetWord1C8(u32 argument0, u32 argument1);
extern u8 *gActorRegistry;

void SetRecordSlotValue(int index, u32 value) {
    void **slots = (void **)(gActorRegistry + 0x20);
    Obj_SetWord1C8((u32)slots[index], value);
}
