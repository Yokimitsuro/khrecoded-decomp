/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

void SetMainBg1Control(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg1cnt = (volatile unsigned short *)0x0400000a;
    *reg_bg1cnt = *reg_bg1cnt & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
