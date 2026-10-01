extern void *Archive_LoadFile();
extern int func_02014d98();
extern void NNSi_FndFreeFromDefaultHeap();

void *func_0202b540(int this_, int arg1, int arg2) {
    void *r = Archive_LoadFile(arg1, arg2);
    if (r == 0) goto ret0;
    if (func_02014d98(r, this_) != 0) return r;
    NNSi_FndFreeFromDefaultHeap(r);
ret0:
    return 0;
}
