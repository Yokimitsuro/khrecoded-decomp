extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02086e58();

int func_ov001_0207ffd4(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_02086e58();
    return 1;
}
