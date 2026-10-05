extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02063ccc();

int func_ov001_020655e8(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_02063ccc();
    return 1;
}
