#include "nitro/types.h"

typedef struct EventTarget {
    u8 pad_00[0x84];
    void *handle;
} EventTarget;

extern void func_ov021_020aafe4(void *handle, u32 value);

void ForwardTargetHandleValue(u32 unused, EventTarget *target, u32 value)
{
    func_ov021_020aafe4(target->handle, value);
}
