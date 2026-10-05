extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_02055638;
extern int sBGAreaOver;

void Bg_SetMainBg3ExtControl(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;
    int arg3;

    DispMode_LookupWordAndDispatch(&data_02055638);
    arg3 = sBGAreaOver;
    *reg_bg3cnt = (*reg_bg3cnt & 0x43) | (arg0 << 14) | (arg2 << 2) | (arg1 << 8) | (arg3 << 13);
}
