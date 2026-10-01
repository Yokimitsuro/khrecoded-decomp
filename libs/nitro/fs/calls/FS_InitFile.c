#include "libs/nitro/fs/fs_internal.h"

void FS_InitFile(FSFile *file)
{
    file->archive = 0;
    file->userdata = 0;
    file->next = 0;
    file->queue->head = file->queue->tail = 0;
    file->status = 0;
    file->status |= FS_COMMAND_INVALID << FS_FILE_STATUS_CMD_SHIFT;
    file->argument = 0;
    file->error = FS_RESULT_SUCCESS;
}
