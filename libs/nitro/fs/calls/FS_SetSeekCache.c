#include "libs/nitro/fs/fs_internal.h"

typedef struct FSArgumentForSetSeekCache {
    void *buffer;
    u32 bufferSize;
} FSArgumentForSetSeekCache;

#define FS_COMMAND_SETSEEKCACHE 34UL

extern BOOL FSi_SendCommand(FSFile *file, FSCommandType command,
                            BOOL blocking);

BOOL FS_SetSeekCache(FSFile *file, void *buffer, u32 bufferSize)
{
    FSArgumentForSetSeekCache argument[1];
    BOOL result = 0;

    file->argument = argument;
    argument->buffer = buffer;
    argument->bufferSize = bufferSize;
    result = FSi_SendCommand(file, FS_COMMAND_SETSEEKCACHE, 1);
    return result;
}
