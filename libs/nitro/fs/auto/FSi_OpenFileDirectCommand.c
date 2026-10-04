#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_OpenFileDirectCommand(FSFile *file)
{
    FSROMFATFileProperty *property =
        (FSROMFATFileProperty *)file->reserved1;
    FSOpenFileDirectInfo *argument =
        (FSOpenFileDirectInfo *)file->reserved2;

    property->top = argument->top;
    property->position = argument->top;
    property->bottom = argument->bottom;
    property->ownId = argument->index;
    return FS_RESULT_SUCCESS;
}
