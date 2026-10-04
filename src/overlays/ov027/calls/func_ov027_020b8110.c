extern int func_ov027_020b79a0(int a);
extern void MI_CpuFill8(void *dst, int val, int size);
extern void NNS_G2dGetUnpackedScreenData(int a, int b);
int func_ov027_020b8110(int a, int b, unsigned short c) {
    int obj = func_ov027_020b79a0(a);
    MI_CpuFill8((void *)obj, 0, 0x10);
    *(unsigned short *)(obj) = c;
    *(int *)(obj + 4) = b;
    NNS_G2dGetUnpackedScreenData(b, obj + 8);
    *(int *)(obj + 0xc) = 1;
    return obj;
}
