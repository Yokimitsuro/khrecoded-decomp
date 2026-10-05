extern void GXS_SetGraphicsMode(int enabled);
void ConfigureOverlay088Display(void) {
    GXS_SetGraphicsMode(0);
    *(volatile unsigned short *)0x0400100c = (*(volatile unsigned short *)0x0400100c & 0x43) | 0xe00;
    *(volatile unsigned short *)0x0400100e = (*(volatile unsigned short *)0x0400100e & 0x43) | 0xf80;
    *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00U) | 0x1c00;
}
