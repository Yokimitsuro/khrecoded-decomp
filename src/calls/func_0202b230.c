extern void func_0202ae90(void *ptr);
extern char data_020556d8;
extern int data_0205a920;

void func_0202b230(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;
    int arg3;

    func_0202ae90(&data_020556d8);
    arg3 = data_0205a920;
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
