#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_SeekDirectory(FSArchive *archive, FSFile *file, u32 id,
                                  u32 position)
{
    FSResult result;
    FSSeekDirInfo *argument = (FSSeekDirInfo *)file->reserved2;

    file->archive = archive;
    argument->position.archive = archive;
    argument->position.ownId = (u16)(id >> 0);
    argument->position.index = (u16)(id >> 16);
    argument->position.position = position;
    result = FSi_TranslateCommand(file, FS_COMMAND_SEEKDIR, 1);
    if (result == FS_RESULT_SUCCESS) {
        file->status |= FS_FILE_STATUS_IS_DIRECTORY;
        file->status &= ~FS_FILE_STATUS_IS_FILE;
        file->archive = archive;
        file->userdata = file->reserved1;
    }
    return result;
}
