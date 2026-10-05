#include "nitro/types.h"

extern void *PXI_Init_0202a64c(u32 unused);
extern u8 data_0205fea8[];

void InitPxiChannelsPair(void)
{
    PXI_Init_0202a64c(*(u32 *)(data_0205fea8 + 0x14));
    PXI_Init_0202a64c(*(u32 *)(data_0205fea8 + 0x18));
}
