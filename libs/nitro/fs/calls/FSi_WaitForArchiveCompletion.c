#include "libs/nitro/fs/fs_internal.h"

FSResult FSi_WaitForArchiveCompletion(FSFile *file, FSResult result)
{
    if (result == FS_RESULT_PROC_ASYNC) {
        FSi_WaitConditionOn(&file->status, FS_FILE_STATUS_ASYNC_DONE,
                            file->queue);
        file->status &= ~FS_FILE_STATUS_ASYNC_DONE;
        result = file->error;
    }
    return result;
}