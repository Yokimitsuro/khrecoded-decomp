typedef unsigned short u16;
typedef enum CARDTargetMode {
    CARD_TARGET_NONE,
    CARD_TARGET_ROM,
    CARD_TARGET_BACKUP,
    CARD_TARGET_RW
} CARDTargetMode;

extern void CARDi_LockResource(u16 owner, CARDTargetMode target);

void CARD_LockBackup(u16 lockId)
{
    CARDi_LockResource(lockId, CARD_TARGET_BACKUP);
}