#include "nitro/types.h"

typedef struct {
    u32 handle;
    u8 pad_04[8];
    u8 fndList[0x34];
} ResourceCacheState;

extern ResourceCacheState *data_ov023_020b6f80;
extern void PXI_Init_0202a64c(u32 arg0);
extern void func_ov001_0207b228(u32 arg0);
extern void DestroyFndListIfNonEmpty(ResourceCacheState *state);

void DestroyResourceCache(void)
{
    ResourceCacheState *state;

    state = data_ov023_020b6f80;
    func_ov001_0207b228(0);
    DestroyFndListIfNonEmpty(state);
    PXI_Init_0202a64c(state->handle);
    data_ov023_020b6f80 = (ResourceCacheState *)0x0;
}
