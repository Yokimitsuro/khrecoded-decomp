#include "libs/nitro/card/card_rom_internal.h"

typedef void (*MIDmaCallback)(void *argument);

extern void func_02000b64(const void *descriptor);
extern void CARD_CheckEnabled(void);
extern u32 CARDi_GetAccessLevel(void);
extern void OS_Terminate(void);
extern BOOL CARDi_WaitForTask(CARDiCommon *common, BOOL restart,
                              MIDmaCallback callback, void *argument);

#define cardi_backup_assert ((const void *)0x02000bac)

void CARDi_BeginBackupCommand(u32 accessLevel, MIDmaCallback callback,
                              void *argument)
{
    func_02000b64(cardi_backup_assert);
    CARD_CheckEnabled();

    if ((CARDi_GetAccessLevel() & accessLevel) != accessLevel) {
        OS_Terminate();
    }

    (void)CARDi_WaitForTask(&cardi_common, 1, callback, argument);
}
