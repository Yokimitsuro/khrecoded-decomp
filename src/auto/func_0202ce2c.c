unsigned int func_0202ce2c(unsigned int param_1) {
    unsigned int mask = 0xfffffc;
    unsigned int base = (param_1 >> 7 & mask) + 0x1ff8000;
    unsigned short lo = param_1 & (mask >> 15);
    int e = *(unsigned short *)(base + 2) & (mask >> 15);

    return *(unsigned int *)(base + ((unsigned int)(((e + 1) / 2) << 0x11) >> 0xf)
                                  + lo * 4 + 0x10) & 0x80000000;
}
