extern int func_0204f494();

void func_ov027_020b97d8(int a, int *b, int c) {
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            func_0204f494(a, v, c);
        }
    }
}
