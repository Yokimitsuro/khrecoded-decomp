int func_ov022_020a9f38(int ctx) {
    unsigned int emitted = *(unsigned int *)(ctx + 0x9c);
    int idx;

    if (emitted >= *(unsigned int *)(ctx + 0xa0)) {
        return 0;
    }
    *(unsigned int *)(ctx + 0x9c) = emitted + 1;
    idx = *(int *)(ctx + 0xc4) + 1;
    *(int *)(ctx + 0xc4) = idx;
    if (idx == *(int *)(ctx + 0xa8)) {
        *(int *)(ctx + 0xc4) = 0;
    }
    return 1;
}
