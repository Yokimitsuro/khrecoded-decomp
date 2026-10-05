extern void PXI_Init_0202a64c(int *arg);

int func_0202a734(int *p) {
    int result = 0;
    if (p[5] == -2) {
        if (p[0] & 1) PXI_Init_0202a64c(p);
        result = 1;
    }
    return result;
}
