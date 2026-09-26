extern int func_02025df8(int a, void *b);
extern void func_ov001_0207f9c0(int a, int b);

int func_ov001_0207fb58(int param_1, unsigned short *param_2) {
    int a = func_02025df8(param_1, param_2);
    int b = func_02025df8(param_1, param_2 + 4);
    func_ov001_0207f9c0(a, b);
    return 1;
}
