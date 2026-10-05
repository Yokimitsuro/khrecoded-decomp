extern int ByteCode_ResolveOperand(int a, void *b);
extern void func_ov031_020bc06c(int a, int b);

int func_ov001_020656a0(int param_1, unsigned short *param_2) {
    int a = ByteCode_ResolveOperand(param_1, param_2);
    int b = ByteCode_ResolveOperand(param_1, param_2 + 4);
    func_ov031_020bc06c(a, b);
    return 1;
}
