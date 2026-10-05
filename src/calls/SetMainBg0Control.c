/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

void SetMainBg0Control(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg0cnt = (volatile unsigned short *)0x04000008;
    *reg_bg0cnt = *reg_bg0cnt & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
