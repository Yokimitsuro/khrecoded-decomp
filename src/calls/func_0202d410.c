extern int NestedPointer_GetFirstWord(int a, int b, int c);
extern int NNS_G3dGetTex(int entry);
extern void NNS_SndPlayerPause_0202a294(int a, int b, int c, int d);

void func_0202d410(int param_1, int param_2, int param_3) {
    int entry = NestedPointer_GetFirstWord(param_1, 7, 0);
    int base;
    if (entry == 0) return;
    base = NNS_G3dGetTex(entry);
    if (base == 0) return;
    NNS_SndPlayerPause_0202a294(param_2, param_1, base + *(int *)(base + 0x14) - param_1, param_3);
}
