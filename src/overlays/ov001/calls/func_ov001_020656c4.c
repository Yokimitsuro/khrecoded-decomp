extern int ScriptVm_ReadOperandInt();
extern int ClearSceneEntry();

int func_ov001_020656c4(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    ClearSceneEntry();
    return 1;
}
