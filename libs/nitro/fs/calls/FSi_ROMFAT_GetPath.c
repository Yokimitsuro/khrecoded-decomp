#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_GetPath(FSArchive *archive, FSFile *file,
                            BOOL isDirectory, char *buffer, u32 *length)
{
    FSResult result;
    FSGetPathInfo *argument = (FSGetPathInfo *)file->reserved2;

    argument->totalLength = 0;
    argument->directoryId = 0;
    argument->buffer = (u8 *)buffer;
    argument->bufferLength = *length;
    result = FSi_TranslateCommand(file, FS_COMMAND_GETPATH, 1);
    if (result == FS_RESULT_SUCCESS) {
        *length = argument->bufferLength;
    }
    (void)archive;
    (void)isDirectory;
    return result;
}
