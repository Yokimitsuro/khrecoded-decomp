extern void *func_0202c48c();
extern int func_02014d98();
extern void func_0202a1d8();

void *func_0202b540(int this_, int arg1, int arg2) {
    void *r = func_0202c48c(arg1, arg2);
    if (r == 0) goto ret0;
    if (func_02014d98(r, this_) != 0) return r;
    func_0202a1d8(r);
ret0:
    return 0;
}
