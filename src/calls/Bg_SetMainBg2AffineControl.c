extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_020556d8;
extern int sBGAreaOver;

void Bg_SetMainBg2AffineControl(int arg0, int arg1, int arg2) {
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    int arg3;

    DispMode_LookupWordAndDispatch(&data_020556d8);
    arg3 = sBGAreaOver;
    *reg_bg2cnt = (*reg_bg2cnt & 0x43) | (arg0 << 14) | (arg1 << 8) | (arg2 << 2) | (arg3 << 13);
}
