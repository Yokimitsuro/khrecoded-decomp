extern int func_02025df8(int a, void *b);
extern void func_ov001_02067cd0(int a, int b);

int func_ov001_02065550(int param_1, unsigned short *param_2) {
    int a = func_02025df8(param_1, param_2);
    int b = func_02025df8(param_1, param_2 + 4);
    func_ov001_02067cd0(a, b);
    return 1;
}
