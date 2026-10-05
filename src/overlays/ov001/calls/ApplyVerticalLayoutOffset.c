#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Context {
    u8 pad_000[0xe8];
    fx32 posX;
    fx32 posY;
    u8 pad_0F0[0x9c];
    fx32 unk_18C;
    fx32 unk_190;
} Context;

extern Context *data_ov001_020a04ec;

void ApplyVerticalLayoutOffset(BOOL raised)
{
    Context *context;
    fx32 offset;

    context = data_ov001_020a04ec;
    offset = 0;
    if (raised) {
        offset = 0xa000;
    }
    context->unk_18C = 0xc000;
    context->unk_190 = offset + 0xe000;
    context->posX = 0;
    context->posY = offset + 0x10000;
}
