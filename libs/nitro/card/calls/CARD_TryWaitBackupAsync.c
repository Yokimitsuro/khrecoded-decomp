typedef int BOOL;
extern BOOL CARDi_TryWaitAsync(void);

BOOL CARD_TryWaitBackupAsync(void)
{
    return CARDi_TryWaitAsync();
}