#include "nitro/types.h"

extern void MIi_CpuClearFast(u32 value, void *dest, u32 size);
extern void OnAnimEventSound(void);

typedef void (*Callback)(void);

typedef struct {
    u32 field0;
    u32 field1;
    u8 pad_008[0x2c];
    Callback callback;
} InitObj;

void InitObjWithCallback(InitObj *obj, u32 arg1, u32 arg2)
{
    MIi_CpuClearFast(0, obj, 0x3c);
    obj->field0 = arg1;
    obj->field1 = arg2;
    obj->callback = OnAnimEventSound;
}
