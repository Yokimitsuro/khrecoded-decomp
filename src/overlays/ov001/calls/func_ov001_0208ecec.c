extern int ScriptVm_ReadOperandInt(int a, void *b);
extern void func_020297c4(int a, int b);

int func_ov001_0208ecec(int param_1, unsigned short *param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandInt(param_1, param_2 + 4);
    func_020297c4(a, b);
    return 1;
}
