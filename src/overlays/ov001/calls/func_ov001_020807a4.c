extern int ScriptVm_ReadOperandInt();
extern int func_ov001_020870a0();

int func_ov001_020807a4(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_020870a0();
    return 1;
}
