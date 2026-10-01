#include "libs/nitro/fs/fs_internal.h"

void FSi_ROMFAT_Idle(FSArchive *archive)
{
    FSFile file[1];

    FS_InitFile(file);
    file->archive = archive;
    (void)FSi_TranslateCommand(file, FS_COMMAND_IDLE, 0);
}
