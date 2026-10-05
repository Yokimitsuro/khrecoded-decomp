/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

extern int gLanguagePath[];
extern void *data_02060394;
extern void *NNSi_FndAllocFromExpHeapEx(int size, void *heap);

void func_0202b774(int n) {
    if (gLanguagePath[1] == 0) {
        gLanguagePath[1] = (int)NNSi_FndAllocFromExpHeapEx(0x40, data_02060394);
    }
    *(short *)gLanguagePath = (short)n;
}
