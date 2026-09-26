extern void func_0202ae5c(void *ptr);
extern char data_02055638;
extern int data_0205a920;

void func_0202b104(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;
    int arg3;

    func_0202ae5c(&data_02055638);
    arg3 = data_0205a920;
    *reg_bg3cnt = (*reg_bg3cnt & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
