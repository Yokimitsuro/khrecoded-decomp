typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern int func_ov027_020ba33c(int a, unsigned b, unsigned short *c, unsigned d, void *va);

unsigned short *func_ov027_020ba300(int a, unsigned b, unsigned short *c, unsigned d, ...) {
    va_list ap;

    va_start(ap, d);
    func_ov027_020ba33c(a, b, c, d, ap);
    return c;
}
