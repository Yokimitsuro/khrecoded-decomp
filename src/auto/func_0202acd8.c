void func_0202acd8(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;
    unsigned short h = *reg_bg2cnt_b;
    *reg_bg2cnt_b = (h & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
