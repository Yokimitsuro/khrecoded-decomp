extern int func_02025df8(void *a);
extern int func_0204da5c(int x);
extern void func_02025e2c(void *a, int b);
extern void func_0204d750(int x);
extern unsigned char data_02055e00;

int func_020266d0(void *obj, int arg1) {
    int r4 = func_02025df8(obj);
    if (func_0204da5c(r4) != 0) {
        func_02025e2c(obj, r4);
        return 0;
    }
    data_02055e00 = r4;
    func_0204d750(r4 & 0xff);
    return 1;
}
