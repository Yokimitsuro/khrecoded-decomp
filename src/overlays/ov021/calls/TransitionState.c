#include "nitro/types.h"

extern void *func_01ffb2f8(void *obj, s32 arg1, s32 value);
extern void func_01ffb12c(void *obj);
extern void GetCurrentNodeOffset(void *obj, void *subobj, s32 arg2);

typedef struct {
    u8 pad_000[0x20];
    u32 flags;
    u8 pad_024[0xfc];
    s32 value;
    s32 state;
    u8 subobj[1];
} StateObj;

void TransitionState(StateObj *obj, s32 value)
{
    if (obj->state != 0 && (obj->state != 2 || value != obj->value)) {
        func_01ffb2f8(obj, 0, value);
        obj->flags = obj->flags | 3;
        func_01ffb12c(obj);
        obj->flags = obj->flags & 0xfffffffc;
        GetCurrentNodeOffset(obj, obj->subobj, 0);
        obj->value = value;
        obj->state = 2;
    }
}
