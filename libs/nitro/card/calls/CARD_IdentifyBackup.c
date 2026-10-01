#include "libs/nitro/card/card_rom_internal.h"

extern void OS_Terminate(void);
extern void CARDi_BeginBackupCommand(u32 accessLevel,
                                      void (*callback)(void *), void *argument);
extern void CARDi_IdentifyBackupCore2(u32 type);
extern BOOL CARDi_ExecuteOldTypeTask(void (*task)(CARDiCommon *common),
                                     BOOL asynchronous);
extern void CARDi_IdentifyBackupCore(CARDiCommon *common);

#define CARD_BACKUP_TYPE_NOT_USE 0

BOOL CARD_IdentifyBackup(u32 type)
{
    if (type == CARD_BACKUP_TYPE_NOT_USE) {
        OS_Terminate();
    }

    CARDi_BeginBackupCommand(0, 0, 0);
    CARDi_IdentifyBackupCore2(type);

    return CARDi_ExecuteOldTypeTask(CARDi_IdentifyBackupCore, 0);
}
