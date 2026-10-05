extern int ByteCode_ResolveOperand(int arg);
extern void EnterPanelModeThree(int arg);
int func_ov001_02065a00(int param_1) {
    EnterPanelModeThree(ByteCode_ResolveOperand(param_1));
    return 0;
}
