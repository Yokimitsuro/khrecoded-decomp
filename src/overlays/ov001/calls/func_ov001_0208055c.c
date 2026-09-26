extern int func_02025df8(void *a, int b);
extern int func_02025e0c(void *a, int b);
extern int func_ov001_02085bd8(unsigned short a, int *b);
extern void func_ov001_0207ee2c(int a, int b);

int func_ov001_0208055c(void *arg1, int arg2) {
    int r1 = func_02025df8(arg1, arg2);
    int r2 = func_02025df8(arg1, arg2 + 8);
    int local = func_02025e0c(arg1, arg2 + 0x10);
    int r = func_ov001_02085bd8((unsigned short)r2, &local);
    func_ov001_0207ee2c(r1, r);
    return 1;
}
