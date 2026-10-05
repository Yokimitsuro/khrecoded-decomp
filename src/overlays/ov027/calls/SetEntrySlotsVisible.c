extern int IndexedRecords_SetFlag2();

void SetEntrySlotsVisible(int a, int *b, int c) {
    unsigned int x;
    int i;
    for (i = 0; i < 2; i++) {
        int v = b[i + 5];
        if (v != -1) {
            IndexedRecords_SetFlag2(a, v, c);
        }
    }
    x = ((c != 0) ? 1u : 0u) << 31;
    b[37] = (((unsigned int)b[37]) & ~2u) | (x >> 30);
}
