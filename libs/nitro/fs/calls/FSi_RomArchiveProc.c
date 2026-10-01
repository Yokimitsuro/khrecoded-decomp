#include "libs/nitro/fs/fs_internal.h"

extern void CARD_LockRom(u16 lockId);
extern void CARD_UnlockRom(u16 lockId);

FSResult FSi_RomArchiveProc(FSFile *file, FSCommandType command)
{
    (void)file;

    switch (command) {
    case FS_COMMAND_ACTIVATE:
        CARD_LockRom((u16)fsi_rom_archive_state.cardLockId);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_IDLE:
        CARD_UnlockRom((u16)fsi_rom_archive_state.cardLockId);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_WRITEFILE:
        return FS_RESULT_UNSUPPORTED;
    default:
        return FS_RESULT_PROC_UNKNOWN;
    }
}