void SetEngineBBG3Control(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *backgroundControl = (volatile unsigned short *)0x0400100e;
    unsigned short previousControl = *backgroundControl;
    *backgroundControl = (previousControl & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
