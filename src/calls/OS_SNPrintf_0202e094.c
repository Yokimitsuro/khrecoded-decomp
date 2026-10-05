extern void *func_0202e0b0();

void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...) {
    return func_0202e0b0(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
