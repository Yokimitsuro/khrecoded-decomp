#include "nitro/types.h"

extern u8 *data_ov001_020a0528;
extern void PXI_Init_0202a64c(u32 handle);

BOOL ReleaseStageManager(void)
{
    if (data_ov001_020a0528 != 0) {
        PXI_Init_0202a64c(*(u32 *)(data_ov001_020a0528 + 4));
        data_ov001_020a0528 = 0;
    }
    return TRUE;
}
