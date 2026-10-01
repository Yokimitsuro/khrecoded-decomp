#include "libs/nitro/fs/fs_overlay_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern const u8 *CARD_GetOwnRomHeader(void);

static inline const CARDRomRegion *CARD_GetRomRegionOVT(MIProcessor target)
{
    const u8 *header = CARD_GetOwnRomHeader();

    return (target == MI_PROCESSOR_ARM9)
               ? (const CARDRomRegion *)(header + 0x50)
               : (const CARDRomRegion *)(header + 0x58);
}

BOOL FS_LoadOverlayInfo(FSOverlayInfo *info, MIProcessor target,
                        FSOverlayID id)
{
    BOOL result = 0;
    const u32 position = id * sizeof(FSOverlayInfoHeader);
    const CARDRomRegion *region = (target == MI_PROCESSOR_ARM9)
                                     ? &FSiOverlayContext.arm9Table
                                     : &FSiOverlayContext.arm7Table;

    if (region->offset) {
        if (position < region->length) {
            FSFile file[1];

            FS_InitFile(file);
            MI_CpuCopy8((const void *)(region->offset + position), info,
                        sizeof(FSOverlayInfoHeader));
            info->target = target;
            if (FS_OpenFileFast(file, FS_GetOverlayFileID(info))) {
                info->filePosition.offset = FS_GetFileImageTop(file);
                info->filePosition.length = FS_GetFileLength(file);
                (void)FS_CloseFile(file);
                result = 1;
            }
        }
    } else {
        region = (target == MI_PROCESSOR_ARM9)
                     ? CARD_GetRomRegionOVT(MI_PROCESSOR_ARM9)
                     : CARD_GetRomRegionOVT(MI_PROCESSOR_ARM7);
        if (position < region->length) {
            FSFile file[1];

            FS_InitFile(file);
            if (FS_CreateFileFromRom(file, region->offset + position,
                                     region->offset + region->length)) {
                if (FS_ReadFile(file, info, sizeof(FSOverlayInfoHeader)) !=
                    sizeof(FSOverlayInfoHeader)) {
                    (void)FS_CloseFile(file);
                } else {
                    (void)FS_CloseFile(file);
                    info->target = target;
                    if (FS_OpenFileFast(file, FS_GetOverlayFileID(info))) {
                        info->filePosition.offset = FS_GetFileImageTop(file);
                        info->filePosition.length = FS_GetFileLength(file);
                        (void)FS_CloseFile(file);
                        result = 1;
                    }
                }
            }
        }
    }
    return result;
}
