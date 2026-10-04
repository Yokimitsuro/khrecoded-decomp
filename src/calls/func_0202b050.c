extern void func_0202ae5c(void *ptr);
extern char data_020556d8;
extern int sBGAreaOver;

void func_0202b050(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    int arg3;

    func_0202ae5c(&data_020556d8);
    arg3 = sBGAreaOver;
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
