#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 mode;
} GroupContext;

extern struct { int reserved; GroupContext *context; } data_ov032_020c0080;

void SetContextModeAndFlag(u8 mode)
{
    data_ov032_020c0080.context->mode = mode;
    data_ov032_020c0080.context->flags |= 0x4000;
}
