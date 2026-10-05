extern void NNS_SndPlayerStopSeqByPlayerNo(int index, int value);

void func_0204d994(void) {
    int index;

    for (index = 2; index < 0x20; index++) {
        NNS_SndPlayerStopSeqByPlayerNo(index, 0);
    }
}
