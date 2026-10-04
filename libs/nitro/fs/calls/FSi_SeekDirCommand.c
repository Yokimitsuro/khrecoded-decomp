#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_SeekDirCommand(FSFile *file)
{
    FSArchive *archive = file->archive;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;
    const FSSeekDirInfo *argument =
        (const FSSeekDirInfo *)file->reserved2;
    FSArchiveFNT entry;
    FSiSyncReadParam parameter;
    FSResult result;

    parameter.archive = archive;
    parameter.position = context->fnt +
                         argument->position.ownId * sizeof(entry);
    result = FSi_ReadTable(&parameter, &entry, sizeof(entry));
    if (result == FS_RESULT_SUCCESS) {
        *(FSDirPos *)file->reserved1 = argument->position;
        if (argument->position.index == 0 &&
            argument->position.position == 0) {
            ((FSROMFATDirProperty *)file->reserved1)->position.index =
                entry.index;
            ((FSROMFATDirProperty *)file->reserved1)->position.position =
                context->fnt + entry.start;
        }
        ((FSROMFATDirProperty *)file->reserved1)->parent =
            entry.parent & 0x0fff;
    }
    return result;
}
