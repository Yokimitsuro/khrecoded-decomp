#include "nitro/types.h"

typedef struct Resource {
    u8 pad_000[0x628];
    s32 ready;
} Resource;

extern void *func_ov036_020bc8c8();

BOOL IsPxiResourceReadyOrInitialize(Resource *resource)
{
    if (resource->ready != 0) {
        return TRUE;
    }
    func_ov036_020bc8c8();
    return TRUE;
}
