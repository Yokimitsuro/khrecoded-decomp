extern void func_0204e978(int *a, int *b, int *c, int d);
void func_0204f18c(int *base, int idx, int scale) {
    char *e4;
    if (idx < 0) {
        return;
    }
    e4 = (char *)(base + 1) + idx * 0x8c;
    *(int *)((char *)base + idx * 0x8c + 0xc) = scale * -0x800;
    func_0204e978(base, (int *)e4, base + 1, (int)base + idx * 0x8c);
}
