#include "nitro/types.h"

extern u32 data_ov036_020c36e0;
extern void PXI_Init_0202a64c(u32 tag);

void InvalidatePxiFifoTag(void)
{
    PXI_Init_0202a64c(data_ov036_020c36e0);
    data_ov036_020c36e0 = 0xffffffff;
}
