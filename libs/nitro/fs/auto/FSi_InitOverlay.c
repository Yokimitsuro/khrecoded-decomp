#include "libs/nitro/fs/fs_overlay_internal.h"

extern const u8 fsiDefaultDigestKey[64];

#define OS_BOOTTYPE_DOWNLOAD_MB 2

typedef struct FSPathStrings {
    char overlayArchiveName[4];
    char rootSuffix[4];
    char romArchiveName[4];
    char romRootPath[8];
} FSPathStrings;

extern int OS_GetBootType(void);
extern FSArchive *FS_FindArchive(const char *name, u32 length);
extern FSPathStrings fsi_path_strings;

void FSi_InitOverlay(void)
{
    if (OS_GetBootType() == OS_BOOTTYPE_DOWNLOAD_MB) {
        FSiOverlayContext.arm9Table.offset = ~0U;
        FSiOverlayContext.arm9Table.length = 0;
        FSiOverlayContext.arm7Table.offset = ~0U;
        FSiOverlayContext.arm7Table.length = 0;
    } else {
        FSiOverlayContext.arm9Table.offset = 0;
        FSiOverlayContext.arm9Table.length = 0;
        FSiOverlayContext.arm7Table.offset = 0;
        FSiOverlayContext.arm7Table.length = 0;
    }

    FSiOverlayContext.digestKey = fsiDefaultDigestKey;
    FSiOverlayContext.digestKeyLength = sizeof(fsiDefaultDigestKey);
    FSiOverlayContext.archive =
        FS_FindArchive(fsi_path_strings.overlayArchiveName, 3);
}
