#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ReadFileCommand(FSFile *file)
{
    FSArchive *archive = file->archive;
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->reserved1;
    FSReadFileInfo *argument = (FSReadFileInfo *)file->reserved2;
    u32 position = property->position;
    u32 length = argument->length;
    void *destination = argument->destination;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;

    property->position = position + length;
    return context->readFunction(archive, destination, position, length);
}
