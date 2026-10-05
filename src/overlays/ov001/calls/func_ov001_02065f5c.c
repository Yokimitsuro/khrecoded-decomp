extern int ScriptVm_ReadOperandInt(int a, int b);
extern int ScriptVm_ReadOperandFx32(int a, int b);
extern void func_ov001_020681b0(int a, int b);
int func_ov001_02065f5c(int param_1, int param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandFx32(param_1, param_2 + 8);
    func_ov001_020681b0(a, b);
    return 1;
}
