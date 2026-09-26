extern unsigned int data_020604d8;
unsigned int func_0202a9e4(unsigned int range) {
    unsigned int *st = &data_020604d8;
    unsigned int r = st[1] * st[0] + st[2];
    st[0] = r;
    if (range == 0) {
        return (unsigned short)(r >> 16);
    }
    return (unsigned short)(((r >> 16) * range) >> 16);
}
