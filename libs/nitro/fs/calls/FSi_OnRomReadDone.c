extern int func_0200a0d8(void);
extern void FS_NotifyArchiveAsyncEnd(void *archive, int status);

void FSi_OnRomReadDone(void *archive)
{
    int status = func_0200a0d8() != 0 ? 5 : 0;
    FS_NotifyArchiveAsyncEnd(archive, status);
}