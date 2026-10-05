extern int ScriptVm_ReadOperandInt();
extern int func_ov001_020674d0();

int func_ov001_02064ecc(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_020674d0();
    return 1;
}
