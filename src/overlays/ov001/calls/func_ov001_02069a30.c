extern void func_0202a1d8();

void func_ov001_02069a30(int arg0) {
    int p = *(int *)(arg0 + 0x1c);
    if (p != 0) {
        func_0202a1d8(p);
        *(int *)(arg0 + 0x1c) = 0;
    }
}
