extern int ScriptVm_ReadOperandInt();
extern int func_ov001_020641d4();

int func_ov001_02065680(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_020641d4();
    return 1;
}
