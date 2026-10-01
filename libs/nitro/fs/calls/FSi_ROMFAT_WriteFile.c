#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_WriteFile(FSArchive *archive, FSFile *file,
                              const void *buffer, u32 *length)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->userdata;
    FSWriteFileInfo *argument = (FSWriteFileInfo *)file->reserved2;
    const u32 position = property->position;
    const u32 remaining = property->bottom - position;
    const u32 originalLength = *length;

    if (*length > remaining) {
        *length = remaining;
    }
    argument->source = buffer;
    argument->originalLength = originalLength;
    argument->length = *length;
    (void)archive;
    return FSi_TranslateCommand(file, FS_COMMAND_WRITEFILE, 0);
}
