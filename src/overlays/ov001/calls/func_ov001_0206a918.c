extern int func_0202a1d8(int block);

int func_ov001_0206a918(int obj) {
    if (*(int *)(obj + 0x2c) != 0) {
        func_0202a1d8(*(int *)(obj + 0x2c));
        *(int *)(obj + 0x2c) = 0;
    }
    *(unsigned char *)(obj + 0x2a) &= ~0xe0;
    return 1;
}
