extern unsigned char *data_0206084c;
extern int RecentRing_Record(void *ptr, int arg);
extern void NNS_SndArcPlayerStartSeqArc(void *ptr, void *arg1, int arg2);

void PlaySoundChecked(void *ptr, int arg) {
    if (ptr == 0) {
        ptr = *(void **)(data_0206084c + 164);
    }

    if (RecentRing_Record(ptr, arg) == 0) {
        return;
    }

    NNS_SndArcPlayerStartSeqArc(data_0206084c + 738524, ptr, arg);
}
