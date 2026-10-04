#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 length);

FSResult FSi_ReadTable(FSiSyncReadParam *parameter, void *destination,
                       u32 length)
{
    FSArchive *archive = parameter->archive;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;
    FSResult result;

    if (context->loadedTables) {
        MI_CpuCopy8((const void *)parameter->position, destination, length);
        result = FS_RESULT_SUCCESS;
    } else {
        result = context->readFunction(archive, destination,
                                       parameter->position, length);
        result = FSi_WaitForArchiveCompletion(archive->list, result);
    }
    parameter->position += length;
    return result;
}
