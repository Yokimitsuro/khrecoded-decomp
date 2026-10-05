extern void func_ov027_020b7ac0(int self);
extern void UpdateTrackedPointerEntry(int self);
struct pend { unsigned char b0 : 1; };
void func_ov027_020b7df4(int param_1) {
    func_ov027_020b7ac0(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        UpdateTrackedPointerEntry(param_1);
}
