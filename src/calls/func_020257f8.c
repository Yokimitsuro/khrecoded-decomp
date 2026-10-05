#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x624];
    u8 pad_624[0x10];
    u32 source;
    u32 param;
    u32 handle;
} PcmChannel;

extern void NNSi_FndFreeFromDefaultHeap(u32 handle);

void func_020257f8(PcmChannel *ch)
{
    if (ch->handle != 0) {
        NNSi_FndFreeFromDefaultHeap(ch->handle);
        ch->handle = 0;
    }
    ch->source = 0;
    ch->param = 0;
}
