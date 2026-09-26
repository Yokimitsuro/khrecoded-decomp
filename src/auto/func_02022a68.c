unsigned short *func_02022a68(unsigned short *dst, unsigned short *src) {
    unsigned short *p = dst, *q;
    unsigned short v;
    do {
        q = p++;
        *q = *src++;
        v = *(volatile unsigned short *)q;
    } while (v != 0);
    return dst;
}
