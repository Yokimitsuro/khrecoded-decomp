extern void *func_0202c48c();
extern int func_02014de4();
extern void NNSi_FndFreeFromDefaultHeap();

void *func_0202b518(int this_, int arg1, int arg2) {
    void *r = func_0202c48c(arg1, arg2);
    if (r == 0) goto ret0;
    if (func_02014de4(r, this_) != 0) return r;
    NNSi_FndFreeFromDefaultHeap(r);
ret0:
    return 0;
}
