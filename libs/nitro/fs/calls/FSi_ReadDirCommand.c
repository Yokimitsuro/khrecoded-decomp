#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_ReadDirCommand(FSFile *file)
{
    FSReadDirInfo *argument = (FSReadDirInfo *)file->reserved2;
    FSDirEntry *entry = argument->entry;
    u8 packedNameLength;
    FSiSyncReadParam parameter;
    FSResult result;

    parameter.archive = file->archive;
    parameter.position =
        ((FSROMFATDirProperty *)file->reserved1)->position.position;
    result = FSi_ReadTable(&parameter, &packedNameLength,
                           sizeof(packedNameLength));
    if (result != FS_RESULT_SUCCESS) {
        return result;
    }

    entry->nameLength = packedNameLength & 0x7f;
    entry->isDirectory = (packedNameLength >> 7) & 1;
    if (entry->nameLength == 0) {
        return FS_RESULT_FAILURE;
    }

    if (!argument->skipName) {
        result = FSi_ReadTable(&parameter, entry->name, entry->nameLength);
        if (result != FS_RESULT_SUCCESS) {
            return result;
        }
        entry->name[entry->nameLength] = '\0';
    } else {
        parameter.position += entry->nameLength;
    }

    if (!entry->isDirectory) {
        entry->id.file.archive = file->archive;
        entry->id.file.fileId =
            ((FSROMFATDirProperty *)file->reserved1)->position.index;
        ++((FSROMFATDirProperty *)file->reserved1)->position.index;
    } else {
        u16 directoryId;

        result = FSi_ReadTable(&parameter, &directoryId,
                               sizeof(directoryId));
        if (result == FS_RESULT_SUCCESS) {
            entry->id.directory.archive = file->archive;
            entry->id.directory.ownId = directoryId & 0x0fff;
            entry->id.directory.index = 0;
            entry->id.directory.position = 0;
        }
    }

    if (result == FS_RESULT_SUCCESS) {
        ((FSROMFATDirProperty *)file->reserved1)->position.position =
            parameter.position;
    }
    return result;
}
