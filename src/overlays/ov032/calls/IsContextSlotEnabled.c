#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6e];
    s8 enabledMask;
} ContextBytes;

extern struct { ContextBytes *context; } data_ov032_020c0080;

BOOL IsContextSlotEnabled(u32 index)
{
    s8 mask = data_ov032_020c0080.context->enabledMask;
    if (mask < 0 || index >= 3) {
        return TRUE;
    }
    return (mask & (1 << index)) != 0;
}
