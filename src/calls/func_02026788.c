extern int func_02025df8(int a, void *b);
extern void func_0204d974(int a, int b, int c);

int func_02026788(int param_1, unsigned short *param_2) {
    int a = func_02025df8(param_1, param_2);
    int b = func_02025df8(param_1, param_2 + 4);
    int c = func_02025df8(param_1, param_2 + 8);
    func_0204d974(a, b, c);
    return 1;
}
