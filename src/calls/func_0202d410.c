extern int func_0202d3f4(int a, int b, int c);
extern int func_0201ac84(int entry);
extern void func_0202a294(int a, int b, int c, int d);

void func_0202d410(int param_1, int param_2, int param_3) {
    int entry = func_0202d3f4(param_1, 7, 0);
    int base;
    if (entry == 0) return;
    base = func_0201ac84(entry);
    if (base == 0) return;
    func_0202a294(param_2, param_1, base + *(int *)(base + 0x14) - param_1, param_3);
}
