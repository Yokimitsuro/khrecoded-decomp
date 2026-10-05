extern int ScriptVm_ReadOperandInt();
extern int func_ov036_020bd090();

int func_ov036_020be1b0(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov036_020bd090();
    return 1;
}
