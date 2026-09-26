extern void GXS_SetGraphicsMode(int mode);

void func_0202ae90(int *table) {
    int mode = table[*(volatile unsigned int *)0x4001000 & 7];
    if (mode >= 8) {
        mode -= 8;
    }
    GXS_SetGraphicsMode(mode);
}
