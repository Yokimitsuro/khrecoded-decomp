extern void func_0202ae5c(void *ptr);
extern char data_020556f8;

void func_0202afe8(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;

    func_0202ae5c(&data_020556f8);
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
