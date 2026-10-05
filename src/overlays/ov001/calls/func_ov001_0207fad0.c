extern int ScriptVm_ReadOperandInt();
extern int func_ov001_0207ee00();

int func_ov001_0207fad0(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_0207ee00();
    return 1;
}
