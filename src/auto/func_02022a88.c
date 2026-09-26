unsigned short *func_02022a88(unsigned short *dst, unsigned short *src, int n) {
    unsigned short *p = dst;
    if (n == 0) return dst;
    do {
        unsigned short *q = p;
        *p++ = *src++;
        if (*(volatile unsigned short *)q == 0) {
            n--;
            if (n != 0) {
                do {
                    *p++ = 0;
                    n--;
                } while (n != 0);
            }
            return dst;
        }
        n--;
    } while (n != 0);
    return dst;
}
