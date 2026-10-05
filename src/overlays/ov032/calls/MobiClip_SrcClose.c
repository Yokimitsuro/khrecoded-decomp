#include "nitro/types.h"

extern u32 data_ov032_020bffe0;
extern void PXI_Init_0202a64c(u32 handle);

/* Releases the MobiClip source handle and invalidates it */
void MobiClip_SrcClose(void) {
    PXI_Init_0202a64c(data_ov032_020bffe0);
    data_ov032_020bffe0 = 0xffffffff;
}
