extern int ByteCode_ResolveOperand(int arg);
extern void StartSessionScene(int arg);
int func_ov001_020651f0(int param_1) {
    StartSessionScene(ByteCode_ResolveOperand(param_1));
    return 0;
}
