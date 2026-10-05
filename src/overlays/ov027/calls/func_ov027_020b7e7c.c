extern int FindFreeRecordSlot_020b790c(int a);
extern void MI_CpuFill8(void *dst, int val, int size);
extern int func_ov027_020b78bc(int a, int b);
int func_ov027_020b7e7c(int a, int b, unsigned short c, unsigned short d, unsigned short e,
                        short f, short g, int h) {
    int obj = FindFreeRecordSlot_020b790c(a);
    MI_CpuFill8((void *)obj, 0, 0x38);
    *(unsigned short *)(obj) = c;
    *(unsigned short *)(obj + 6) = d;
    *(unsigned short *)(obj + 8) = e;
    *(int *)(obj + 0x10) = h;
    *(short *)(obj + 0xa) = f;
    *(short *)(obj + 0xc) = g;
    *(int *)(obj + 0x18) = func_ov027_020b78bc(a, b);
    *(int *)(obj + 0x14) = 1;
    return obj;
}
