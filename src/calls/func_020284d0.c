#include "nitro/types.h"

extern void NNS_GfdRegisterNewVramTransferTask(u32 a, u32 b, u32 c, u32 d);

void func_020284d0(u32 context)
{
    u32 sub = *(u32 *)(context + 0x5c);
    NNS_GfdRegisterNewVramTransferTask(0xb, 0, sub + 0xc, *(u32 *)(sub + 8));
}
