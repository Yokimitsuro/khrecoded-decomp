#include "nitro/types.h"

typedef struct EventTarget {
    u8 pad_00[0x84];
    void *handle;
} EventTarget;

extern void ResetEntryStates(void *handle);

void ForwardTargetHandle_020d3b60(u32 unused, EventTarget *target)
{
    ResetEntryStates(target->handle);
}
