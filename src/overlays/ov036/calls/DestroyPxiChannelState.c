#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 handle;
} PxiChannelState;

extern PxiChannelState *data_ov036_020ca204;
extern void *func_ov036_020c2884();
extern void *PXI_Init_02028964();

void DestroyPxiChannelState(void)
{
    func_ov036_020c2884(data_ov036_020ca204->handle);
    PXI_Init_02028964();
    data_ov036_020ca204->handle = 0xffffffff;
    data_ov036_020ca204 = (PxiChannelState *)0;
}
