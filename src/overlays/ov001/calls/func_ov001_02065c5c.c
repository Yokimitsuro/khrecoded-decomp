extern int ScriptVm_ReadOperandInt(int a, int b);
extern int ByteCode_ResolveOperand(int a, int b);
extern void SetSessionTableName(int a, int b);
int func_ov001_02065c5c(int param_1, int param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ByteCode_ResolveOperand(param_1, param_2 + 8);
    SetSessionTableName(a, b);
    return 1;
}
