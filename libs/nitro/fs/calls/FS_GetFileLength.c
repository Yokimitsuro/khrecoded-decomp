#include "libs/nitro/fs/fs_internal.h"

typedef struct FSArgumentForGetFileLength {
    u32 length;
} FSArgumentForGetFileLength;

#define FS_COMMAND_GETFILELENGTH 15UL

extern BOOL FSi_GetFileLengthIfProc(FSFile *file, u32 *length);
extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

u32 FS_GetFileLength(FSFile *file)
{
    u32 result = 0;

    if (!FSi_GetFileLengthIfProc(file, &result)) {
        FSArgumentForGetFileLength argument[1];

        file->argument = argument;
        argument->length = 0;
        if (FSi_SendCommand(file, FS_COMMAND_GETFILELENGTH, 1)) {
            result = argument->length;
        }
    }
    return result;
}
