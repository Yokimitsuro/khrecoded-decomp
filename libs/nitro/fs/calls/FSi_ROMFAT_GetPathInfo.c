#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuFill8(void *destination, u8 value, u32 length);

FSResult FSi_ROMFAT_GetPathInfo(FSArchive *archive, u32 baseDirectoryId,
                                const char *path, FSPathInfo *info)
{
    FSResult result = FS_RESULT_ERROR;
    u32 id = 0;

    MI_CpuFill8(info, 0, sizeof(*info));
    if (FSi_ROMFAT_FindPath(archive, baseDirectoryId, path, &id, 1) ==
        FS_RESULT_SUCCESS) {
        info->attributes = FS_ATTRIBUTE_IS_DIRECTORY;
        info->id = id;
        result = FS_RESULT_SUCCESS;
    } else if (FSi_ROMFAT_FindPath(archive, baseDirectoryId, path, &id, 0) ==
               FS_RESULT_SUCCESS) {
        info->attributes = 0;
        info->id = id;
        info->fileSize = 0;

        {
            FSROMFATArchiveContext *context =
                (FSROMFATArchiveContext *)archive->userdata;
            u32 position = id * sizeof(FSArchiveFAT);

            if (position < context->fatSize) {
                FSArchiveFAT allocation;
                FSiSyncReadParam parameter;

                parameter.archive = archive;
                parameter.position = context->fat + position;
                if (FSi_ReadTable(&parameter, &allocation,
                                  sizeof(allocation)) == FS_RESULT_SUCCESS) {
                    info->fileSize = allocation.bottom - allocation.top;
                    if (FSi_IsUnreadableRomOffset(archive, allocation.top)) {
                        info->attributes |= FS_ATTRIBUTE_IS_OFFLINE;
                    }
                }
            }
        }
        result = FS_RESULT_SUCCESS;
    }

    info->attributes |= FS_ATTRIBUTE_IS_PROTECTED;
    return result;
}