extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02064884();

int func_ov001_02065ce4(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_02064884();
    return 1;
}
