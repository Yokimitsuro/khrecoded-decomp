extern void func_0202ae90(void *ptr);
extern char data_02055698;

void func_0202b1fc(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg3cnt_b = (volatile unsigned short *)0x0400100e;

    func_0202ae90(&data_02055698);
    *reg_bg3cnt_b = (*reg_bg3cnt_b & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
