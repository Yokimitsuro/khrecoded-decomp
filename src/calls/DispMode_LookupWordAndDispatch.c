extern void *GX_SetGraphicsMode();

void *DispMode_LookupWordAndDispatch(int *tbl) {
    volatile unsigned int *reg = (volatile unsigned int *)0x4000000;
    int v = tbl[*reg & 7];
    int on = (*reg & 8) != 0;
    int b2 = on != 0;
    if (v >= 8) {
        v -= 8;
    }
    return GX_SetGraphicsMode(1, v, b2);
}
