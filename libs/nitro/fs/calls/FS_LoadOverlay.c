#include "libs/nitro/fs/fs_overlay_internal.h"

BOOL FS_LoadOverlay(MIProcessor target, FSOverlayID id)
{
    BOOL result = 0;
    FSOverlayInfo info;

    if (FS_LoadOverlayInfo(&info, target, id)) {
        if (FS_LoadOverlayImage(&info)) {
            FS_StartOverlay(&info);
            result = 1;
        }
    }
    return result;
}
