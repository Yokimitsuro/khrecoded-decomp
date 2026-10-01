#include "libs/nitro/gx/gx_load_internal.h"
#include "libs/nitro/gx/gx_load_state_internal.h"

void GX_LoadTex(const void *source, u32 offset, u32 size)
{
    void *destination;

    if (gGXTextureLoadState.texLCDCBase2 == 0) {
        destination = (void *)(gGXTextureLoadState.texLCDCBase1 + offset);
    } else {
        if (offset + size < gGXTextureLoadState.texBlock1Size) {
            destination = (void *)(gGXTextureLoadState.texLCDCBase1 + offset);
        } else if (offset >= gGXTextureLoadState.texBlock1Size) {
            destination = (void *)(gGXTextureLoadState.texLCDCBase2 + offset -
                                   gGXTextureLoadState.texBlock1Size);
        } else {
            void *secondDestination =
                (void *)gGXTextureLoadState.texLCDCBase2;
            u32 firstSize = gGXTextureLoadState.texBlock1Size - offset;
            destination =
                (void *)(gGXTextureLoadState.texLCDCBase1 + offset);

            GXi_DmaCopy32(GXi_DmaId, source, destination, firstSize);
            GXi_DmaCopy32Async(GXi_DmaId,
                               (const u8 *)source + firstSize,
                               secondDestination, size - firstSize, 0, 0);
            return;
        }
    }

    GXi_DmaCopy32Async(GXi_DmaId, source, destination, size, 0, 0);
}
