/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
struct Bits {
    unsigned int b0 : 3;
    unsigned int flag : 1;
    unsigned int rest : 28;
};

struct Elem {
    struct Bits bits;
    char pad2[0x8c - 4];
};

struct Outer {
    char pad[0x7c];
    struct Elem arr[1];
};

void IndexedRecords_SetFlag3(struct Outer *base, int index, int value) {
    if (index < 0) return;
    base->arr[index].bits.flag = (value != 0);
}
