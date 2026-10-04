#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_WriteFileCommand(FSFile *file)
{
    FSArchive *archive = file->archive;
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->reserved1;
    FSWriteFileInfo *argument = (FSWriteFileInfo *)file->reserved2;
    u32 position = property->position;
    u32 length = argument->length;
    const void *source = argument->source;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;

    property->position = position + length;
    return context->writeFunction(archive, source, position, length);
}
