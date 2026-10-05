extern int IndexedRecord_SetActive();

void func_ov027_020b9640(int a, int *b) {
    int i;
    int v;
    for (i = 0; i < 2; i++) {
        v = b[i + 5];
        if (v != -1) {
            IndexedRecord_SetActive(a, v);
        }
    }
}
