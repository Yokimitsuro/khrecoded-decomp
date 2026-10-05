extern int ScriptVm_ReadOperandInt();
extern int LoadSceneTable();

int func_ov001_02064ecc(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    LoadSceneTable();
    return 1;
}
