#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_CloseDirectory(FSArchive *archive, FSFile *file)
{
    file->userdata = 0;
    file->status &= ~(FS_FILE_STATUS_IS_FILE | FS_FILE_STATUS_IS_DIRECTORY);
    (void)archive;
    return FS_RESULT_SUCCESS;
}
