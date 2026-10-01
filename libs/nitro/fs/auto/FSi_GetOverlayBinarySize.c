#include "libs/nitro/fs/fs_overlay_internal.h"

u32 FSi_GetOverlayBinarySize(const FSOverlayInfo *info)
{
    return (info->header.flags & FS_OVERLAY_FLAG_COMPRESSED)
               ? info->header.compressedSize
               : info->header.ramSize;
}
