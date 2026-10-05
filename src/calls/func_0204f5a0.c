extern void MI_CpuFill8(void *p, int v, unsigned int n);
extern void MIi_CpuClear16(int v, void *p, unsigned int n);

int func_0204f5a0(short *record, short *limits) {
    MI_CpuFill8(record, 0, 0x1a);
    if (limits != 0) {
        record[1] = limits[0] >= 0 ? (unsigned short)limits[0] : 0xf;
        record[2] = limits[1] >= 0 ? (unsigned short)limits[1] : 4;
    } else {
        record[1] = 0xf;
        record[2] = 4;
    }
    MIi_CpuClear16(0, record + 3, 0x14);
    return 1;
}
