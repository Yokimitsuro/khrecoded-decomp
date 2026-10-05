extern int ScriptVm_ReadOperandInt();
extern int func_ov001_0208c164();

int func_ov001_0208ee58(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_0208c164();
    return 1;
}
