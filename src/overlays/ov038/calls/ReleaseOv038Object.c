#include "nitro/types.h"

extern u32 data_ov038_020bbda0;
extern void PXI_Init_0202a64c(u32 handle);

void ReleaseOv038Object(void)
{
    PXI_Init_0202a64c(data_ov038_020bbda0);
    data_ov038_020bbda0 = 0xffffffff;
}
