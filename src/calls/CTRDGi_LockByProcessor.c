#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern u16 OS_ReadOwnerOfLockWord(void *lockWord);
extern s32 OS_TryLockCartridge(u16 lockID);
extern void WaitByLoop(s32 count);

void CTRDGi_LockByProcessor(u16 lockID, CTRDGLockByProc *info)
{
    while (1) {
        info->irq = OS_DisableInterrupts();
        if (((info->locked = OS_ReadOwnerOfLockWord((void *)0x02ffffe8) & 0x40) != 0)
            || (OS_TryLockCartridge(lockID) == 0)) {
            break;
        }
        OS_RestoreInterrupts(info->irq);
        WaitByLoop(1);
    }
}
