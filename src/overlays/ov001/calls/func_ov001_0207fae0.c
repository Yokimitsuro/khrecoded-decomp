extern int func_02025df8(int a, void *b);
extern void func_ov001_0207eedc(int a, int b, int c);

int func_ov001_0207fae0(int param_1, unsigned short *param_2) {
    int a = func_02025df8(param_1, param_2);
    int b = func_02025df8(param_1, param_2 + 4);
    int c = func_02025df8(param_1, param_2 + 8);
    func_ov001_0207eedc(a, b, c);
    return 1;
}
