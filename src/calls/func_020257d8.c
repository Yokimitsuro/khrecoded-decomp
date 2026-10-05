#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x624];
    u8 pad_624[0x10];
    u32 source;
    u32 param;
    u32 handle;
} PcmChannel;

extern u32 NNSi_FndAllocFromDefaultHeap(u32 source);

void func_020257d8(PcmChannel *ch, u32 source, u32 param)
{
    ch->source = source;
    ch->handle = NNSi_FndAllocFromDefaultHeap(source);
    ch->param = param;
}
