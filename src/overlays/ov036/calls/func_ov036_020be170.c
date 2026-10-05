extern int ScriptVm_ReadOperandInt(void *self, void *desc);
extern void func_ov036_020bcfec(int a, int b, int c, int d);

int func_ov036_020be170(void *self, char *descs) {
    int a = ScriptVm_ReadOperandInt(self, descs);
    int b = ScriptVm_ReadOperandInt(self, descs + 8);
    int c = ScriptVm_ReadOperandInt(self, descs + 0x10);
    int d = ScriptVm_ReadOperandInt(self, descs + 0x18);

    func_ov036_020bcfec(a, b, c, d);
    return 1;
}
