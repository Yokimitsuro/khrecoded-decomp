#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ROMFAT_ReadFile(FSArchive *archive, FSFile *file, void *buffer,
                             u32 *length)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->userdata;
    FSReadFileInfo *argument = (FSReadFileInfo *)file->reserved2;
    const u32 position = property->position;
    const u32 remaining = property->bottom - position;
    const u32 originalLength = *length;

    if (*length > remaining) {
        *length = remaining;
    }
    argument->destination = buffer;
    argument->originalLength = originalLength;
    argument->length = *length;
    (void)archive;
    return FSi_TranslateCommand(file, FS_COMMAND_READFILE, 0);
}
