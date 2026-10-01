#include "libs/nitro/fs/fs_overlay_internal.h"

extern u32 FSi_GetOverlayBinarySize(const FSOverlayInfo *info);
extern void FS_ClearOverlayImage(FSOverlayInfo *info);

BOOL FS_LoadOverlayImage(FSOverlayInfo *info)
{
    BOOL result = 0;
    FSFile file[1];

    FS_InitFile(file);
    if (FS_OpenFileFast(file, FS_GetOverlayFileID(info))) {
        s32 size = FSi_GetOverlayBinarySize(info);
        FS_ClearOverlayImage(info);
        if (FS_ReadFile(file, FS_GetOverlayAddress(info), size) == size) {
            result = 1;
        }
        (void)FS_CloseFile(file);
    }
    return result;
}
