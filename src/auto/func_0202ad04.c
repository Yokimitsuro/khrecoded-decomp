void func_0202ad04(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg1cnt_b = (volatile unsigned short *)0x0400100a;
    *reg_bg1cnt_b = *reg_bg1cnt_b & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
