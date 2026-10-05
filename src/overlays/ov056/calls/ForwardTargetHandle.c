#include "nitro/types.h"

typedef struct EventTarget {
    u8 pad_00[0x84];
    void *handle;
} EventTarget;

extern void func_ov021_020aaff4(void *handle);

void ForwardTargetHandle(u32 unused, EventTarget *target)
{
    func_ov021_020aaff4(target->handle);
}
