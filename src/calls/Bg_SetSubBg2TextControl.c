extern void SetSubEngineGraphicsModeFromTable(void *ptr);
extern char data_020556f8;

void Bg_SetSubBg2TextControl(int arg0, int arg1, int arg2, int arg3) {
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;

    SetSubEngineGraphicsModeFromTable(&data_020556f8);
    *reg_bg2cnt_b = (*reg_bg2cnt_b & 0x43) | (arg0 << 14) | (arg1 << 7) | (arg2 << 8) | (arg3 << 2);
}
