extern int func_0204f23c(int a, int b);
int func_ov027_020b967c(int a, int *tbl) {
    int i;
    int r;
    int m1;
    int v;
    r = 0;
    i = r;
    m1 = -1;
    do {
        v = tbl[i + 5];
        if (v != m1) {
            r = func_0204f23c(a, v);
            break;
        }
        i = i + 1;
    } while (i < 2);
    return r;
}
