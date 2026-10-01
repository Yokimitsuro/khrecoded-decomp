extern void *OSi_DoUnlockByWord();
extern void OSi_FreeCartridgeBus(void);

void *OS_UnlockCartridge_0x020022c8(int id)
{
    return OSi_DoUnlockByWord(id, (void *)0x02ffffe8, OSi_FreeCartridgeBus, 1);
}