#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_CloseFile(FSArchive *archive, FSFile *file)
{
    FSResult result;

    result = FSi_TranslateCommand(file, FS_COMMAND_CLOSEFILE, 1);
    file->userdata = 0;
    file->status &= ~(FS_FILE_STATUS_IS_FILE | FS_FILE_STATUS_IS_DIRECTORY);
    (void)archive;
    return result;
}
