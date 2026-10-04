#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_SeekDirDirect(FSFile *file, u32 directoryId)
{
    FSSeekDirInfo *argument = (FSSeekDirInfo *)file->reserved2;

    argument->position.archive = file->archive;
    argument->position.ownId = directoryId;
    argument->position.index = 0;
    argument->position.position = 0;
    return FSi_TranslateCommand(file, FS_COMMAND_SEEKDIR, 1);
}
