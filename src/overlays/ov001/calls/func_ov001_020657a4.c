extern int ScriptVm_ReadOperandFx32(int a, void *b);
extern void func_ov042_020bd7c8(int a, int b);

int func_ov001_020657a4(int param_1, unsigned short *param_2) {
    int a = ScriptVm_ReadOperandFx32(param_1, param_2);
    int b = ScriptVm_ReadOperandFx32(param_1, param_2 + 4);
    func_ov042_020bd7c8(a, b);
    return 1;
}
