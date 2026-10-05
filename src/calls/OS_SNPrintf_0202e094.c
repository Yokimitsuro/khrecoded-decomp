extern void *Text_VSNPrintfWide();

void *OS_SNPrintf_0202e094(char *dst, unsigned int len, const char *fmt, ...) {
    return Text_VSNPrintfWide(dst, len, fmt, (void *)(((unsigned int)&fmt & ~3u) + 4));
}
