int func_ov022_020aa150(int cur, int src) {
    *(int *)(cur + 0xc) = src;
    *(int *)(cur + 4) = *(int *)(src + 0x28) - *(int *)(src + 0x24);
    *(int *)(cur + 8) = *(int *)(*(int *)(cur + 0xc) + 0x2c) - *(int *)(*(int *)(cur + 0xc) + 0x24);
    *(char *)(cur + 0x10) = 0;
    return 1;
}
