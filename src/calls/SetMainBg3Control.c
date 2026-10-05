/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

void SetMainBg3Control(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *reg_bg3cnt = (volatile unsigned short *)0x0400000e;
    unsigned short h = *reg_bg3cnt;
    *reg_bg3cnt = (h & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
