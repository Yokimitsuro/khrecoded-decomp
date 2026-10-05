#include "nitro/types.h"

extern u32 data_ov028_020bb320;
extern void PXI_Init_0202a64c(u32 handle);

void ReleaseHandle_020bb0a4(void)
{
    PXI_Init_0202a64c(data_ov028_020bb320);
    data_ov028_020bb320 = 0xffffffff;
}
