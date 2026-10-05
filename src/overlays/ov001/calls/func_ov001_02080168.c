extern int ScriptVm_ReadOperandInt(void *self, void *desc);
extern int func_02025e0c(void *self, void *desc);
extern void func_ov001_0207fa24(int a, int b, int c, int d);

int func_ov001_02080168(void *self, char *descs) {
    int a = ScriptVm_ReadOperandInt(self, descs);
    int b = ScriptVm_ReadOperandInt(self, descs + 8);
    int c = func_02025e0c(self, descs + 0x10);
    int d = func_02025e0c(self, descs + 0x18);

    func_ov001_0207fa24(a, b, c, d);
    return 1;
}
