#include "nitro/types.h"
#include "nitro/ctrdg.h"

extern struct {
    BOOL enableFlag;
    CTRDGWork work;
} data_0205a2a0;


extern BOOL CTRDGi_HasValidModuleInfo(void);
extern void CTRDGi_LockByProcessor(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_UnlockByProcessor(u16 lockID, CTRDGLockByProc *info);
extern void CTRDGi_ChangeLatestAccessCycle(CTRDGRomCycle *r);
extern void CTRDGi_RestoreAccessCycle(CTRDGRomCycle *r);

BOOL CTRDG_IsExisting(void)
{
    BOOL retval = TRUE;
    CTRDGLockByProc lockInfo;

    CTRDGHeader *chp = (CTRDGHeader *)0x08000000;
    CTRDGModuleInfo *cip = (CTRDGModuleInfo *)0x02fffc30;

    if (!CTRDGi_HasValidModuleInfo()) {
        return FALSE;
    }

    if (cip->detectPullOut == TRUE) {
        return FALSE;
    }
    CTRDGi_LockByProcessor(data_0205a2a0.work.lockID, &lockInfo);

    {
        CTRDGRomCycle rc;
        u8 isRomCode;

        CTRDGi_ChangeLatestAccessCycle(&rc);
        isRomCode = chp->isRomCode;

        if ((isRomCode == CTRDG_IS_ROM_CODE && cip->moduleID.raw != chp->moduleID)
            || (isRomCode != CTRDG_IS_ROM_CODE && cip->moduleID.raw != *(u16 *)0x0801fffe)
            || ((cip->gameCode != chp->gameCode) && cip->isAgbCartridge)) {
            cip->detectPullOut = TRUE;
            retval = FALSE;
        }

        CTRDGi_RestoreAccessCycle(&rc);
    }

    CTRDGi_UnlockByProcessor(data_0205a2a0.work.lockID, &lockInfo);
    return retval;
}
