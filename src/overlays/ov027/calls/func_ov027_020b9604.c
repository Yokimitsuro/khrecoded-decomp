extern int IndexedRecord_ClearActive();

void func_ov027_020b9604(int a, int *b) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = b[i + 5];
        if (v != -1) {
            IndexedRecord_ClearActive(a, v);
        }
    }
}
