#include "libs/nitro/fs/fs_overlay_internal.h"

extern void IC_InvalidateRange(void *address, u32 size);
extern void DC_InvalidateRange(void *address, u32 size);
extern void MI_CpuFill8(void *destination, int value, u32 size);

void FS_ClearOverlayImage(FSOverlayInfo *info)
{
    u8 *address = FS_GetOverlayAddress(info);
    u32 imageSize = FS_GetOverlayImageSize(info);
    u32 totalSize = FS_GetOverlayTotalSize(info);

    IC_InvalidateRange(address, totalSize);
    DC_InvalidateRange(address, totalSize);
    MI_CpuFill8(address + imageSize, 0, totalSize - imageSize);
}
