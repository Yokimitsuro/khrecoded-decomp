#include "nitro/types.h"

extern u32 data_ov035_020bc480;
extern void *PXI_Init_0202a64c(u32 handle);

void MobiClip_SrcClose_020ba9e0(void) {
    PXI_Init_0202a64c(data_ov035_020bc480);
    data_ov035_020bc480 = 0xffffffff;
}
