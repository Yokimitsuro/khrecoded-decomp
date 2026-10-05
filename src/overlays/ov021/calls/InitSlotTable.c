#include "nitro/types.h"

extern void MI_CpuFill8(void *dest, u32 value, u32 size);

typedef struct {
    u8 pad_000[0x2c];
} Slot;

typedef struct {
    u8 pad_000[0x114];
    Slot slots[6];
    u32 field21c;
    u32 field220;
    u32 field224;
    u32 pad_228;
    u8 kind;
    u8 pad_22d[3];
} Obj;

void InitSlotTable(Obj *obj, u8 kind)
{
    int i = 0;
    MI_CpuFill8(obj, 0, sizeof(Obj));
    obj->kind = kind;
    do {
        *(u32 *)&obj->slots[i] = 0;
        i++;
    } while (i < 6);
    obj->field21c = 0;
    obj->field224 = 0;
    obj->field220 = 0;
}
