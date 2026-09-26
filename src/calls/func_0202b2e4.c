extern void func_0202ae90(void *ptr);
extern char data_02055638;
extern int data_0205a920;

void func_0202b2e4(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg3cnt_b = (volatile unsigned short *)0x0400100e;
    int arg3;

    func_0202ae90(&data_02055638);
    arg3 = data_0205a920;
    *reg_bg3cnt_b = (*reg_bg3cnt_b & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
