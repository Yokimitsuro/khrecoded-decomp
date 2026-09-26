extern int func_02025df8(void *self, void *desc);
extern void func_ov036_020bd590(int a, int b, int c, int d);

int func_ov036_020be4ec(void *self, char *descs) {
    int a = func_02025df8(self, descs);
    int b = func_02025df8(self, descs + 8);
    int c = func_02025df8(self, descs + 0x10);
    int d = func_02025df8(self, descs + 0x18);

    func_ov036_020bd590(a, b, c, d);
    return 1;
}
