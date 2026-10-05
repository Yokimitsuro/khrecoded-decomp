extern int ScriptVm_ReadOperandInt(int a, void *b);
extern void ReallocTableEntry(int a, int b);

int func_ov001_02080020(int param_1, unsigned short *param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandInt(param_1, param_2 + 4);
    ReallocTableEntry(a, b);
    return 1;
}
