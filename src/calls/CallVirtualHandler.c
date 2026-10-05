#include "nitro/types.h"

typedef void (*Handler)(void *, void *, void *, void *, void *, void *);

void CallVirtualHandler(void **context, void *arg2, void *arg3, void *arg4, void *arg5)
{
    u8 *base = (u8 *)context[8] + 0xc;
    Handler handler = *(Handler *)*(u32 *)(base + 0x14);
    handler(base, context[0], arg2, arg3, arg4, arg5);
}
