extern int ScriptVm_ReadOperandInt();
extern int func_ov001_0206a860();

int func_ov001_02065910(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_0206a860();
    return 1;
}
