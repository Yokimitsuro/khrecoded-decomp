typedef int BOOL;
extern BOOL CARDi_WaitAsync(void);

BOOL CARD_WaitBackupAsync(void)
{
    return CARDi_WaitAsync();
}