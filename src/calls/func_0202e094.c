extern void func_0202e0b0(int a, int b, int c, void *ap);

void func_0202e094(int a, int b, int c, ...) {
    func_0202e0b0(a, b, c, (void *)(((unsigned int)&c & ~3u) + 4));
}
