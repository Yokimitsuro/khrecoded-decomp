extern void *func_02014e14();
extern void func_02014d88();

int func_02014d4c(int this_, int *arg1) {
    void *r = func_02014e14(this_, 0x43484152);
    if (r == 0) {
        *arg1 = 0;
        return 0;
    }
    func_02014d88((char *)r + 8);
    *arg1 = (int)((char *)r + 8);
    return 1;
}
