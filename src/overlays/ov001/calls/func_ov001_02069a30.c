extern void NNSi_FndFreeFromDefaultHeap();

void func_ov001_02069a30(int arg0) {
    int p = *(int *)(arg0 + 0x1c);
    if (p != 0) {
        NNSi_FndFreeFromDefaultHeap(p);
        *(int *)(arg0 + 0x1c) = 0;
    }
}
