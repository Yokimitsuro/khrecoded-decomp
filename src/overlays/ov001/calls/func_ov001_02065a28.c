extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02064328();

int func_ov001_02065a28(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_02064328();
    return 1;
}
