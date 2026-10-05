/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern unsigned short **func_01ffb2d4(void);

int func_0202f4cc(void) {
    unsigned short **p;
    p = func_01ffb2d4();
    if (!p) {
        return 0;
    }
    return p[2][2] << 12;
}
