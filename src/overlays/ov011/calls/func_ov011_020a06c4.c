extern int ScriptVm_ReadOperandInt();
extern int func_ov001_0207f050();
extern int func_ov011_020a1144();

int func_ov011_020a06c4(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    func_ov001_0207f050();
    func_ov011_020a1144();
    return 1;
}
