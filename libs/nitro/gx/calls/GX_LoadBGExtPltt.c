#include "libs/nitro/gx/gx_load_internal.h"
#include "libs/nitro/gx/gx_load_state_internal.h"

void GX_LoadBGExtPltt(const void *source, u32 offset, u32 size)
{
    void *destination =
        (void *)(gGXExtPlttLoadState.bgExtPlttLCDCBase + offset -
                 gGXExtPlttLoadState.bgExtPlttLCDCOffset);
    GXi_DmaCopy32Async(GXi_DmaId, source, destination, size, 0, 0);
}
