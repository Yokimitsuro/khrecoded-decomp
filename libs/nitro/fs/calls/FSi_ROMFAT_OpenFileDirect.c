#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_OpenFileDirect(FSArchive *archive, FSFile *file, u32 top,
                                   u32 bottom, u32 *id)
{
    FSResult result;
    FSOpenFileDirectInfo *argument =
        (FSOpenFileDirectInfo *)file->reserved2;

    argument->top = top;
    argument->bottom = bottom;
    argument->index = *id;
    result = FSi_TranslateCommand(file, FS_COMMAND_OPENFILEDIRECT, 1);
    if (result == FS_RESULT_SUCCESS) {
        file->status |= FS_FILE_STATUS_IS_FILE;
        file->status &= ~FS_FILE_STATUS_IS_DIRECTORY;
        file->archive = archive;
        file->userdata = file->reserved1;
    }
    return result;
}
