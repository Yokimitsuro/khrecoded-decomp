#include "libs/nitro/fs/fs_overlay_internal.h"

#define FS_OVERLAY_DIGEST_SIZE 20
#define OS_BOOTTYPE_ROM 1

extern u8 SDK_OVERLAY_DIGEST[];
extern u8 SDK_OVERLAY_DIGEST_END[];

extern int OS_GetBootType(void);
extern BOOL FSi_CompareDigest(const u8 *expectedDigest, void *source,
                              int length, BOOL tableMode);
extern void MI_CpuFill8(void *destination, int value, u32 size);
extern void OS_Terminate(void);
extern void MIi_UncompressBackward(void *end);
extern void DC_FlushRange(void *address, u32 size);
extern u32 FSi_GetOverlayBinarySize(const FSOverlayInfo *info);

void FS_StartOverlay(FSOverlayInfo *info)
{
    u32 loadedSize = FSi_GetOverlayBinarySize(info);

    if (OS_GetBootType() != OS_BOOTTYPE_ROM) {
        BOOL valid = 0;

        if ((info->header.flags & FS_OVERLAY_FLAG_AUTHENTICATED) != 0) {
            const u32 digestCount =
                (SDK_OVERLAY_DIGEST_END - SDK_OVERLAY_DIGEST) /
                FS_OVERLAY_DIGEST_SIZE;

            if (info->header.id < digestCount) {
                const u8 *expectedDigest =
                    SDK_OVERLAY_DIGEST +
                    FS_OVERLAY_DIGEST_SIZE * info->header.id;

                valid = FSi_CompareDigest(expectedDigest,
                                          info->header.ramAddress,
                                          loadedSize, 0);
            }
        }
        if (!valid) {
            MI_CpuFill8(info->header.ramAddress, 0, loadedSize);
            OS_Terminate();
            return;
        }
    }

    if ((info->header.flags & FS_OVERLAY_FLAG_COMPRESSED) != 0) {
        MIi_UncompressBackward(info->header.ramAddress + loadedSize);
    }
    DC_FlushRange(FS_GetOverlayAddress(info), FS_GetOverlayImageSize(info));

    {
        FSOverlayInitFunction *current = info->header.staticInitializers;
        FSOverlayInitFunction *end = info->header.staticInitializersEnd;

        for (; current < end; ++current) {
            if (*current) {
                (**current)();
            }
        }
    }
}
