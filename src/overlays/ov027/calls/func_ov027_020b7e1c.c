extern void func_ov027_020b833c(int);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov027_020b7e1c(int param_1) {
    void *p;
    func_ov027_020b833c(param_1);
    p = *(void **)(param_1 + 0x14); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
    p = *(void **)(param_1 + 0x10); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
    p = *(void **)(param_1 + 0xc); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
}
