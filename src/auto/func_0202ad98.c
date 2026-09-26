void func_0202ad98(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *reg_bg2cnt = (volatile unsigned short *)0x0400000c;
    unsigned short h = *reg_bg2cnt;
    *reg_bg2cnt = (h & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
