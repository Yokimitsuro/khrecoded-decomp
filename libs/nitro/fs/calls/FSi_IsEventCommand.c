#include "libs/nitro/fs/fs_internal.h"

extern void FSi_ROMFAT_Activate(FSArchive *archive);
extern void FSi_ROMFAT_Idle(FSArchive *archive);
extern void FSi_ROMFAT_Suspend(FSArchive *archive);
extern void FSi_ROMFAT_Resume(FSArchive *archive);
extern void FSi_ROMFAT_Unmount(FSArchive *archive);

const FSArchiveInterface FSiArchiveProcInterface = {
    (FSArchiveMethod)FSi_ROMFAT_ReadFile,
    (FSArchiveMethod)FSi_ROMFAT_WriteFile,
    (FSArchiveMethod)FSi_ROMFAT_SeekDirectory,
    (FSArchiveMethod)FSi_ROMFAT_ReadDirectory,
    (FSArchiveMethod)FSi_ROMFAT_FindPath,
    (FSArchiveMethod)FSi_ROMFAT_GetPath,
    (FSArchiveMethod)FSi_ROMFAT_OpenFileFast,
    (FSArchiveMethod)FSi_ROMFAT_OpenFileDirect,
    (FSArchiveMethod)FSi_ROMFAT_CloseFile,
    (FSArchiveMethod)FSi_ROMFAT_Activate,
    (FSArchiveMethod)FSi_ROMFAT_Idle,
    (FSArchiveMethod)FSi_ROMFAT_Suspend,
    (FSArchiveMethod)FSi_ROMFAT_Resume,
    (FSArchiveMethod)FSi_ROMFAT_OpenFile,
    (FSArchiveMethod)FSi_ROMFAT_SeekFile,
    (FSArchiveMethod)FSi_ROMFAT_GetFileLength,
    (FSArchiveMethod)FSi_ROMFAT_GetFilePosition,
    0,
    (FSArchiveMethod)FSi_ROMFAT_Unmount,
    (FSArchiveMethod)FSi_ROMFAT_GetArchiveCaps,
    0,
    0,
    0,
    (FSArchiveMethod)FSi_ROMFAT_GetPathInfo,
    0,
    0,
    0,
    0,
    (FSArchiveMethod)FSi_ROMFAT_GetArchiveResource,
    0,
    0,
    0,
    (FSArchiveMethod)FSi_ROMFAT_OpenDirectory,
    (FSArchiveMethod)FSi_ROMFAT_CloseDirectory,
    0,
    {0}
};

BOOL FSi_IsEventCommand(FSCommandType command)
{
    return command == FS_COMMAND_ACTIVATE ||
           command == FS_COMMAND_IDLE ||
           command == FS_COMMAND_SUSPEND ||
           command == FS_COMMAND_RESUME ||
           command == FS_COMMAND_MOUNT ||
           command == FS_COMMAND_UNMOUNT ||
           command == FS_COMMAND_INVALID;
}