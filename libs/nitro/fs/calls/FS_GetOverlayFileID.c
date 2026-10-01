#include "libs/nitro/fs/fs_overlay_internal.h"

FSFileID FS_GetOverlayFileID(const FSOverlayInfo *info)
{
    FSFileID result;

    result.archive = FSiOverlayContext.archive;
    result.fileId = info->header.fileId;
    return result;
}
