extern unsigned char *gSoundWork;
extern int RecentRing_Record(void *ptr, int arg);
extern void NNS_SndArcPlayerStartSeqArc(void *ptr, void *arg1, int arg2);

void PlaySoundChecked(void *ptr, int arg) {
    if (ptr == 0) {
        ptr = *(void **)(gSoundWork + 164);
    }

    if (RecentRing_Record(ptr, arg) == 0) {
        return;
    }

    NNS_SndArcPlayerStartSeqArc(gSoundWork + 738524, ptr, arg);
}
