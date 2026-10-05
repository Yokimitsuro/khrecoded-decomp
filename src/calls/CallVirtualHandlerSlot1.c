#include "nitro/types.h"

typedef void (*Handler)(void *, int);

void CallVirtualHandlerSlot1(void **context, int arg)
{
    u8 *base = (u8 *)context[8] + 0xc;
    Handler handler = *(Handler *)(*(u32 *)(base + 0x14) + 4);
    handler(base, arg);
}
