typedef unsigned short u16;
typedef enum CARDTargetMode {
    CARD_TARGET_NONE,
    CARD_TARGET_ROM,
    CARD_TARGET_BACKUP,
    CARD_TARGET_RW
} CARDTargetMode;

extern int CARD_TryWaitBackupAsync(void);
extern int CARD_WaitBackupAsync(void);
extern void CARDi_UnlockResource(u16 owner, CARDTargetMode target);

void CARD_UnlockBackup(u16 lockId)
{
    if (!CARD_TryWaitBackupAsync()) {
        (void)CARD_WaitBackupAsync();
    }
    CARDi_UnlockResource(lockId, CARD_TARGET_BACKUP);
}