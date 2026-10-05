#include "nitro/types.h"

extern void G2x_SetBlendAlpha_(void *blendControl, u32 plane1, u32 plane2, u32 eva, u32 evb);

void SetupBgBlend(void)
{
    *(vu16 *)0x0400000e = (*(vu16 *)0x0400000e & ~3) | 1;
    *(vu16 *)0x0400000c = (*(vu16 *)0x0400000c & ~3) | 2;
    G2x_SetBlendAlpha_((void *)0x04000050, 4, 1, 10, 6);
}
