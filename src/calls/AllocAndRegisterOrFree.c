extern void *Archive_LoadFile();
extern int NNS_G2dGetUnpackedScreenData();
extern void NNSi_FndFreeFromDefaultHeap();

void *AllocAndRegisterOrFree(int this_, int arg1, int arg2) {
    void *r = Archive_LoadFile(arg1, arg2);
    if (r == 0) goto ret0;
    if (NNS_G2dGetUnpackedScreenData(r, this_) != 0) return r;
    NNSi_FndFreeFromDefaultHeap(r);
ret0:
    return 0;
}
