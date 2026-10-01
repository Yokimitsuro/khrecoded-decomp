#include "libs/nitro/fs/fs_overlay_internal.h"

BOOL FS_UnloadOverlayImage(FSOverlayInfo *info)
{
    FS_EndOverlay(info);
    return 1;
}
