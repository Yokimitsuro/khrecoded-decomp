extern void func_0202ae90(void *ptr);
extern char data_020556f8;

void func_0202b1c8(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;

    func_0202ae90(&data_020556f8);
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
