/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

struct X {
    char _0[0x18];
    unsigned int flags;
};

void func_020524fc(struct X *p) {
    MI_CpuFill8(p, 0, 0x1c);
    p->flags &= ~1;
    p->flags &= ~2;
    p->flags |= 4;
}
