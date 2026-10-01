extern int func_0202c4a0(int data, int kind);
extern void func_ov027_020b8f7c(int self, int obj, int arg);
extern void NNSi_FndFreeFromDefaultHeap(void *obj);
void func_ov027_020b8fb8(int param_1, int param_2, int param_3) {
    int obj = func_0202c4a0(param_2, 0xe);
    func_ov027_020b8f7c(param_1, obj, param_3);
    if (obj != 0) NNSi_FndFreeFromDefaultHeap((void *)obj);
}
