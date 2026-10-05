/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
struct Inner {
    unsigned int b0 : 2;
    unsigned int flag : 1;
    unsigned int rest : 29;
    char pad[0x8c - 4];
};

void IndexedRecords_SetFlag2(int *base, int index, int value) {
    struct Inner *p;
    if (index < 0) return;
    p = (struct Inner *)((char *)base + 0x7c);
    p[index].flag = (value != 0);
}
