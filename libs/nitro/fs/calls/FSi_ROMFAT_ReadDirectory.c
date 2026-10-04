#include "libs/nitro/fs/fs_internal.h"

extern void MI_CpuCopy8(const void *source, void *destination, u32 length);

FSResult FSi_ROMFAT_ReadDirectory(FSArchive *archive, FSFile *file,
                                  FSDirectoryEntryInfo *info)
{
    FSResult result;
    FSDirEntry entry[1];
    FSROMFATCommandInfo *argument = (FSROMFATCommandInfo *)file->reserved2;

    argument->readDirectory.entry = entry;
    argument->readDirectory.skipName = 0;
    result = FSi_TranslateCommand(file, FS_COMMAND_READDIR, 1);
    if (result == FS_RESULT_SUCCESS) {
        info->shortNameLength = 0;
        info->longNameLength = entry->nameLength;
        MI_CpuCopy8(entry->name, info->longName, info->longNameLength);
        info->longName[info->longNameLength] = '\0';
        if (entry->isDirectory) {
            info->attributes = FS_ATTRIBUTE_IS_DIRECTORY;
            info->id = (u32)((entry->id.directory.ownId << 0) |
                             (entry->id.directory.index << 16));
            info->fileSize = 0;
        } else {
            info->attributes = 0;
            info->id = entry->id.file.fileId;
            info->fileSize = 0;

            {
                FSROMFATArchiveContext *context =
                    (FSROMFATArchiveContext *)archive->userdata;
                u32 position = (u32)(info->id * sizeof(FSArchiveFAT));

                if (position < context->fatSize) {
                    FSArchiveFAT allocation;
                    FSiSyncReadParam parameter;

                    parameter.archive = archive;
                    parameter.position = context->fat + position;
                    if (FSi_ReadTable(&parameter, &allocation,
                                      sizeof(allocation)) == FS_RESULT_SUCCESS) {
                        info->fileSize = allocation.bottom - allocation.top;
                        if (FSi_IsUnreadableRomOffset(archive,
                                                      allocation.top)) {
                            info->attributes |= FS_ATTRIBUTE_IS_OFFLINE;
                        }
                    }
                }
            }
        }
        info->modificationTime.year = 0;
        info->modificationTime.month = 0;
        info->modificationTime.day = 0;
        info->modificationTime.hour = 0;
        info->modificationTime.minute = 0;
        info->modificationTime.second = 0;
    }
    return result;
}