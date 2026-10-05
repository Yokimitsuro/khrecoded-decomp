/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

void SetMainBg2Control(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    unsigned short h = *reg_bg2cnt;
    *reg_bg2cnt = (h & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
