extern int Slot_SetMode2Bit();

void func_ov027_020b97d8(int a, int *b, int c) {
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            Slot_SetMode2Bit(a, v, c);
        }
    }
}
