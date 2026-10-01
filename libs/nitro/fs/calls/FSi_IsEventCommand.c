#include "libs/nitro/fs/fs_internal.h"

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