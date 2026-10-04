extern void *NNS_G2dFindBinaryBlock();
extern void NNS_G2dUnpackBGNCG();

int NNS_G2dGetUnpackedBGCharacterData(int this_, int *arg1) {
    void *r = NNS_G2dFindBinaryBlock(this_, 0x43484152);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    NNS_G2dUnpackBGNCG((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
