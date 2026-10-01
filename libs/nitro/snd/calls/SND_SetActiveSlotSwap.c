extern int sCurrentSoundArchive;

int SND_SetActiveSlotSwap(int arg0)
{
    int old = sCurrentSoundArchive;
    sCurrentSoundArchive = arg0;
    return old;
}
