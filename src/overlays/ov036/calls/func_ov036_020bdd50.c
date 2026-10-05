extern int ScriptVm_ReadOperandInt(int a, void *b);
extern void func_ov036_020bce7c(int a, int b);

int func_ov036_020bdd50(int param_1, unsigned short *param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandInt(param_1, param_2 + 4);
    func_ov036_020bce7c(a, b);
    return 1;
}
