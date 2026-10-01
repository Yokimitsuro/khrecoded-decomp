extern int CARD_IsPulledOut(void);
extern void FS_NotifyArchiveAsyncEnd(void *archive, int status);

void FSi_OnRomReadDone(void *archive)
{
    int status = CARD_IsPulledOut() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(archive, status);
}