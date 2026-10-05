#include "nitro/types.h"

extern u32 Obj_SetWord1C8(u32 argument0, u32 argument1);
extern u8 *data_0206083c;

void SetRecordSlotValue(int index, u32 value) {
    void **slots = (void **)(data_0206083c + 0x20);
    Obj_SetWord1C8((u32)slots[index], value);
}
