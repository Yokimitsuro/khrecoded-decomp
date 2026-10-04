#include "libs/nitro/fs/fs_internal.h"

FSResult (*const fsi_default_command[])(FSFile *) = {
    FSi_ReadFileCommand,
    FSi_WriteFileCommand,
    FSi_SeekDirCommand,
    FSi_ReadDirCommand,
    FSi_FindPathCommand,
    FSi_GetPathCommand,
    FSi_OpenFileFastCommand,
    FSi_OpenFileDirectCommand,
    FSi_CloseFileCommand,
    FSi_CloseFileCommand,
    FSi_CloseFileCommand,
    FSi_CloseFileCommand,
    FSi_CloseFileCommand
};
