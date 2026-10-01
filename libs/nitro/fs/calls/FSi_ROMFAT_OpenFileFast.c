#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_OpenFileFast(FSArchive *archive, FSFile *file, u32 id,
                                 u32 mode)
{
    FSResult result;
    FSOpenFileFastInfo *argument =
        (FSOpenFileFastInfo *)file->reserved2;

    argument->id.archive = archive;
    argument->id.fileId = id;
    result = FSi_TranslateCommand(file, FS_COMMAND_OPENFILEFAST, 1);
    if (result == FS_RESULT_SUCCESS) {
        file->status |= FS_FILE_STATUS_IS_FILE;
        file->status &= ~FS_FILE_STATUS_IS_DIRECTORY;
        file->archive = archive;
        file->userdata = file->reserved1;
    }
    (void)mode;
    return result;
}
