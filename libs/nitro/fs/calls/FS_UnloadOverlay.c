#include "libs/nitro/fs/fs_overlay_internal.h"

BOOL FS_UnloadOverlay(MIProcessor target, FSOverlayID id)
{
    BOOL result = 0;
    FSOverlayInfo info;

    if (FS_LoadOverlayInfo(&info, target, id)) {
        if (FS_UnloadOverlayImage(&info)) {
            result = 1;
        }
    }
    return result;
}
