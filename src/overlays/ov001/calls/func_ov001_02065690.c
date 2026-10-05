extern int ScriptVm_ReadOperandInt();
extern int SetSceneLock();

int func_ov001_02065690(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    SetSceneLock();
    return 1;
}
