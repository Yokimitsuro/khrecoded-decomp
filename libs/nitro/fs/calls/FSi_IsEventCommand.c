#include "libs/nitro/fs/fs_internal.h"

extern void FSi_ROMFAT_ReadFile(void);
extern void FSi_ROMFAT_WriteFile(void);
extern void FSi_ROMFAT_SeekDirectory(void);
extern void FSi_ROMFAT_ReadDirectory(void);
extern void FSi_ROMFAT_FindPath(void);
extern void FSi_ROMFAT_GetPath(void);
extern void FSi_ROMFAT_OpenFileFast(void);
extern void FSi_ROMFAT_OpenFileDirect(void);
extern void FSi_ROMFAT_CloseFile(void);
extern void FSi_ROMFAT_Activate(void);
extern void FSi_ROMFAT_Idle(void);
extern void FSi_ROMFAT_Suspend(void);
extern void FSi_ROMFAT_Resume(void);
extern void FSi_ROMFAT_OpenFile(void);
extern void FSi_ROMFAT_SeekFile(void);
extern void FSi_ROMFAT_GetFileLength(void);
extern void FSi_ROMFAT_GetFilePosition(void);
extern void FSi_ROMFAT_Unmount(void);
extern void FSi_ROMFAT_GetArchiveCaps(void);
extern void FSi_ROMFAT_GetPathInfo(void);
extern void FSi_ROMFAT_GetArchiveResource(void);
extern void FSi_ROMFAT_OpenDirectory(void);
extern void FSi_ROMFAT_CloseDirectory(void);

const FSArchiveInterface FSiArchiveProcInterface = {
    FSi_ROMFAT_ReadFile,
    FSi_ROMFAT_WriteFile,
    FSi_ROMFAT_SeekDirectory,
    FSi_ROMFAT_ReadDirectory,
    FSi_ROMFAT_FindPath,
    FSi_ROMFAT_GetPath,
    FSi_ROMFAT_OpenFileFast,
    FSi_ROMFAT_OpenFileDirect,
    FSi_ROMFAT_CloseFile,
    FSi_ROMFAT_Activate,
    FSi_ROMFAT_Idle,
    FSi_ROMFAT_Suspend,
    FSi_ROMFAT_Resume,
    FSi_ROMFAT_OpenFile,
    FSi_ROMFAT_SeekFile,
    FSi_ROMFAT_GetFileLength,
    FSi_ROMFAT_GetFilePosition,
    0,
    FSi_ROMFAT_Unmount,
    FSi_ROMFAT_GetArchiveCaps,
    0,
    0,
    0,
    FSi_ROMFAT_GetPathInfo,
    0,
    0,
    0,
    0,
    FSi_ROMFAT_GetArchiveResource,
    0,
    0,
    0,
    FSi_ROMFAT_OpenDirectory,
    FSi_ROMFAT_CloseDirectory,
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