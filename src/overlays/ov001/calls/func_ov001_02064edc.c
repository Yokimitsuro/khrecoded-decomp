extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02067618();

int func_ov001_02064edc(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_02067618();
    return 1;
}
