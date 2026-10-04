#include "libs/nitro/fs/fs_internal.h"

#define FS_DIRECTORY_ID_INVALID 0x10000UL

extern u32 STD_GetStringLength(const char *text);
extern void MI_CpuCopy8(const void *source, void *destination, u32 length);

static inline BOOL FS_IsDirectory(volatile const FSFile *file)
{
    return (file->status & FS_FILE_STATUS_IS_DIRECTORY) != 0;
}

FSResult FSi_GetPathCommand(FSFile *file)
{
    FSArchive *const archive = file->archive;
    FSGetPathInfo *info = (FSGetPathInfo *)file->reserved2;
    FSDirEntry entry;
    FSFile temporary;
    u32 directoryId;
    u32 fileId;
    u32 id;
    u32 length;
    const BOOL blocking = 1;
    const FSCommandType readCommand = FS_COMMAND_READDIR;

    FS_InitFile(&temporary);
    temporary.archive = archive;

    if (FS_IsDirectory(file)) {
        directoryId = ((FSROMFATDirProperty *)file->reserved1)->position.ownId;
        fileId = FS_DIRECTORY_ID_INVALID;
    } else {
        u32 position = 0;
        u32 directoryCount = 0;

        fileId = ((FSROMFATFileProperty *)file->reserved1)->ownId;
        directoryId = FS_DIRECTORY_ID_INVALID;
        do {
            (void)FSi_SeekDirDirect(&temporary, position);
            if (position == 0) {
                directoryCount =
                    ((FSROMFATDirProperty *)temporary.reserved1)->parent;
            }

            ((FSReadDirInfo *)temporary.reserved2)->entry = &entry;
            ((FSReadDirInfo *)temporary.reserved2)->skipName = blocking;
            while (FSi_TranslateCommand(&temporary, readCommand, blocking) ==
                   FS_RESULT_SUCCESS) {
                if (!entry.isDirectory && entry.id.file.fileId == fileId) {
                    directoryId =
                        ((FSROMFATDirProperty *)temporary.reserved1)
                            ->position.ownId;
                    break;
                }
            }
        } while (directoryId == FS_DIRECTORY_ID_INVALID &&
                 ++position < directoryCount);
    }

    if (directoryId == FS_DIRECTORY_ID_INVALID) {
        info->totalLength = 0;
        return FS_RESULT_NO_ENTRY;
    }

    id = directoryId;
    length = STD_GetStringLength(FS_GetArchiveName(archive)) + 2;
    (void)FSi_SeekDirDirect(&temporary, id);

    if (fileId != FS_DIRECTORY_ID_INVALID) {
        length += entry.nameLength;
    }
    if (id != 0) {
        do {
            (void)FSi_SeekDirDirect(
                &temporary,
                ((FSROMFATDirProperty *)temporary.reserved1)->parent);
            ((FSReadDirInfo *)temporary.reserved2)->entry = &entry;
            ((FSReadDirInfo *)temporary.reserved2)->skipName = blocking;
            while (FSi_TranslateCommand(&temporary, readCommand, blocking) ==
                   FS_RESULT_SUCCESS) {
                if (entry.isDirectory && entry.id.directory.ownId == id) {
                    length += entry.nameLength + 1;
                    break;
                }
            }
            id = ((FSROMFATDirProperty *)temporary.reserved1)->position.ownId;
        } while (id != 0);
    }

    info->totalLength = (u16)(length + 1);
    info->directoryId = (u16)directoryId;

    if (info->buffer != 0 && info->bufferLength >= info->totalLength) {
        u8 *destination = info->buffer;
        u32 total = info->totalLength;
        u32 position = 0;
        const char *archiveName = FS_GetArchiveName(archive);

        length = STD_GetStringLength(archiveName);
        MI_CpuCopy8(archiveName, destination + position, length);
        position += length;
        MI_CpuCopy8(fsi_path_strings.pathRootSuffix, destination + position, 2);
        position += 2;

        id = directoryId;
        (void)FSi_SeekDirDirect(&temporary, id);
        if (fileId != FS_DIRECTORY_ID_INVALID) {
            ((FSReadDirInfo *)temporary.reserved2)->entry = &entry;
            ((FSReadDirInfo *)temporary.reserved2)->skipName = 0;
            while (FSi_TranslateCommand(&temporary, readCommand, blocking) ==
                   FS_RESULT_SUCCESS) {
                if (!entry.isDirectory && entry.id.file.fileId == fileId) {
                    break;
                }
            }
            length = entry.nameLength + 1;
            MI_CpuCopy8(entry.name, destination + total - length, length);
            total -= length;
        } else {
            destination[total - 1] = '\0';
            --total;
        }

        if (id != 0) {
            do {
                (void)FSi_SeekDirDirect(
                    &temporary,
                    ((FSROMFATDirProperty *)temporary.reserved1)->parent);
                ((FSReadDirInfo *)temporary.reserved2)->entry = &entry;
                ((FSReadDirInfo *)temporary.reserved2)->skipName = 0;
                destination[total - 1] = '/';
                --total;
                while (FSi_TranslateCommand(&temporary, readCommand,
                                             blocking) == FS_RESULT_SUCCESS) {
                    if (entry.isDirectory && entry.id.directory.ownId == id) {
                        length = entry.nameLength;
                        MI_CpuCopy8(entry.name,
                                    destination + total - length, length);
                        total -= length;
                        break;
                    }
                }
                id = ((FSROMFATDirProperty *)temporary.reserved1)
                         ->position.ownId;
            } while (id != 0);
        }
    }

    return FS_RESULT_SUCCESS;
}