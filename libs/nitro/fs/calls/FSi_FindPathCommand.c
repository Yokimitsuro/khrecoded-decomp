#include "libs/nitro/fs/fs_internal.h"

extern int FSi_IncrementSjisPositionToSlash(const char *text, int position);

static inline int FSi_StrNICmp(const char *left, const char *right, u32 length)
{
    int difference = 0;
    u32 position = 0;

    while (position < length) {
        u32 leftCharacter = (u32)(left[position] - 'A') & 0xff;
        u32 rightCharacter = (u32)(right[position] - 'A') & 0xff;

        if (leftCharacter <= 'Z' - 'A') {
            leftCharacter += 'a' - 'A';
        }
        if (rightCharacter <= 'Z' - 'A') {
            rightCharacter += 'a' - 'A';
        }
        difference = (int)(leftCharacter - rightCharacter);
        if (difference != 0) {
            break;
        }
        ++position;
    }
    return difference;
}

FSResult FSi_FindPathCommand(FSFile *directory)
{
    const char *path = ((FSFindPathInfo *)directory->reserved2)->path;
    const BOOL findDirectory =
        ((FSFindPathInfo *)directory->reserved2)->findDirectory;
    const BOOL blocking = 1;

    (void)FSi_TranslateCommand(directory, FS_COMMAND_SEEKDIR, blocking);

    for (; *path != '\0'; path += (*path != '\0' ? 1 : 0)) {
        int nameLength = FSi_IncrementSjisPositionToSlash(path, 0);
        BOOL isDirectory = path[nameLength] != '\0' || findDirectory;

        if (nameLength == 0) {
            return FS_RESULT_INVALID_PARAMETER;
        }
        if (*path == '.') {
            if (nameLength == 1) {
                ++path;
                continue;
            }
            if (nameLength == 2 && path[1] == '.') {
                FSROMFATDirProperty *property =
                    (FSROMFATDirProperty *)directory->reserved1;

                if (property->position.ownId != 0) {
                    (void)FSi_SeekDirDirect(directory, property->parent);
                }
                path += 2;
                continue;
            }
        } else if (*path == '*') {
            break;
        }

        if (nameLength > 127) {
            return FS_RESULT_NO_ENTRY;
        }

        {
            FSDirEntry entry;
            FSReadDirInfo *readDirectory =
                (FSReadDirInfo *)directory->reserved2;

            readDirectory->entry = &entry;
            readDirectory->skipName = 0;
            for (;;) {
                if (FSi_TranslateCommand(directory, FS_COMMAND_READDIR,
                                         blocking) != FS_RESULT_SUCCESS) {
                    return FS_RESULT_NO_ENTRY;
                }
                if (isDirectory != entry.isDirectory ||
                    (u32)nameLength != entry.nameLength ||
                    FSi_StrNICmp(path, entry.name, (u32)nameLength) != 0) {
                    continue;
                }

                if (isDirectory) {
                    *(FSSeekDirInfo *)directory->reserved2 =
                        *(FSSeekDirInfo *)&entry.id.directory;
                    path += nameLength;
                    (void)FSi_TranslateCommand(directory,
                                               FS_COMMAND_SEEKDIR, blocking);
                    break;
                }
                if (findDirectory) {
                    return FS_RESULT_NO_ENTRY;
                }
                *(((FSFindPathInfo *)directory->reserved2)->result.file) =
                    entry.id.file;
                return FS_RESULT_SUCCESS;
            }
        }
    }

    if (!findDirectory) {
        return FS_RESULT_NO_ENTRY;
    }
    *(((FSFindPathInfo *)directory->reserved2)->result.directory) =
        ((FSROMFATDirProperty *)directory->reserved1)->position;
    return FS_RESULT_SUCCESS;
}