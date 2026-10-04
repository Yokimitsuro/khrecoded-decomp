#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_OpenFileFastCommand(FSFile *file)
{
    FSArchive *archive = file->archive;
    FSROMFATArchiveContext *context =
        (FSROMFATArchiveContext *)archive->userdata;
    FSOpenFileFastInfo *argument = (FSOpenFileFastInfo *)file->reserved2;
    const u32 index = argument->id.fileId;
    u32 position = index * sizeof(FSArchiveFAT);

    if (position >= context->fatSize) {
        return FS_RESULT_NO_ENTRY;
    }

    {
        FSArchiveFAT fat;
        FSiSyncReadParam parameter;
        FSResult result;

        parameter.archive = archive;
        parameter.position = context->fat + position;
        result = FSi_ReadTable(&parameter, &fat, sizeof(fat));
        if (result == FS_RESULT_SUCCESS) {
            FSOpenFileDirectInfo *direct =
                (FSOpenFileDirectInfo *)file->reserved2;

            direct->top = fat.top;
            direct->bottom = fat.bottom;
            direct->index = index;
            result = FSi_TranslateCommand(file,
                                          FS_COMMAND_OPENFILEDIRECT, 1);
        }
        return result;
    }
}
