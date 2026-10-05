#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x66];
    s8 values[8];
    s8 enabled;
} ContextBytes;

extern struct { ContextBytes *context; } data_ov032_020c0080;

int GetContextIndexedByte(u32 index)
{
    ContextBytes *context = data_ov032_020c0080.context;
    if (context->enabled < 0 || index >= 3) {
        return context->values[0];
    }
    return context->values[index];
}
