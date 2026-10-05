#include "nitro/types.h"

extern u32 data_ov037_020bb6c0;
extern void *PXI_Init_0202a64c();

void ReleasePxiChannel(void)
{
    PXI_Init_0202a64c(data_ov037_020bb6c0);
    data_ov037_020bb6c0 = 0xffffffff;
}
