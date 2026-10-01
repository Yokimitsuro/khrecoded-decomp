extern void *OSi_DoTryLockByWord();
extern void OSi_AllocateCartridgeBus(void);

void *OS_TryLockCartridge(int id)
{
    return OSi_DoTryLockByWord(id, (void *)0x02ffffe8, OSi_AllocateCartridgeBus, 1);
}