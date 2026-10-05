extern int ScriptVm_ReadOperandInt();
extern int func_ov001_0206890c();

int func_ov001_020655d8(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_0206890c();
    return 1;
}
