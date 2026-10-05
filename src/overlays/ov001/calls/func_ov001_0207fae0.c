extern int ScriptVm_ReadOperandInt(int a, void *b);
extern void PrependListNode(int a, int b, int c);

int func_ov001_0207fae0(int param_1, unsigned short *param_2) {
    int a = ScriptVm_ReadOperandInt(param_1, param_2);
    int b = ScriptVm_ReadOperandInt(param_1, param_2 + 4);
    int c = ScriptVm_ReadOperandInt(param_1, param_2 + 8);
    PrependListNode(a, b, c);
    return 1;
}
