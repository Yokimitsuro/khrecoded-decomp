#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

typedef struct {
    u8 pad_000[0x1c];
    s32 field1c;
    u32 pad_020;
    s32 field24;
    u8 pad_028[0x24];
    s32 field4c;
    u8 pad_050[8];
    s16 field58;
    s16 field5a;
    u8 field5c;
    u8 mode : 4;
    u8 upper : 4;
    u8 pad_05e[2];
} Obj;

void ResetMotionState(Obj *obj)
{
    MI_CpuFill8(obj, 0, sizeof(Obj));
    obj->field1c = -0x1000;
    obj->field24 = -0x1000;
    obj->field5a = -1;
    obj->field4c = -1;
    obj->field58 = obj->field5a;
    obj->mode = 1;
}
