#include "nitro/types.h"

extern void PXI_Init_0202a64c();
extern u32 data_ov029_020bab80;

void ReleaseOv029Object(void)
{
    PXI_Init_0202a64c(data_ov029_020bab80);
    data_ov029_020bab80 = 0xffffffff;
}
