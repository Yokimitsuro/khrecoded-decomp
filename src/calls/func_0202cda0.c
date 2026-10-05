extern int strlen(void *a);
extern int PXI_Init_02022af8(void *a, void *b, int c);

int func_0202cda0(unsigned char *arg0, void *arg1) {
    int i;
    unsigned char *p;
    int r0;
    unsigned short count;

    r0 = strlen(arg1);
    count = (unsigned short)(*(unsigned short *)(arg0 + 2) & 0x1ff);
    p = (arg0 + 0x10) + (((unsigned int)((count + 1) / 2) << 17) >> 15);
    p += count * 4;
    for (i = 0; i < count; i++) {
        if (PXI_Init_02022af8(p, arg1, r0) == 0) {
            return i;
        }
        p += 8;
    }
    return -1;
}
