extern void DispMode_LookupWordAndDispatch(void *ptr);
extern char data_02055698;

void Bg_SetMainBg3TextControl(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;

    DispMode_LookupWordAndDispatch(&data_02055698);
    *reg_bg3cnt = (*reg_bg3cnt & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
