#include "libs/nitro/fs/fs_internal.h"

#define FS_ARCHIVE_FLAG_CANCELING 0x00000020UL

static inline BOOL FS_IsBusy(volatile const FSFile *file)
{
    return (file->status & FS_FILE_STATUS_BUSY) != 0;
}

void FS_CancelFile(FSFile *file)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    if (FS_IsBusy(file)) {
        file->status |= FS_FILE_STATUS_CANCEL;
        file->archive->flags |= FS_ARCHIVE_FLAG_CANCELING;
    }
    (void)OS_RestoreInterrupts(interruptState);
}
