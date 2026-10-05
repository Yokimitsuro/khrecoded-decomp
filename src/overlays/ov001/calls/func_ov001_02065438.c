extern int ScriptVm_ReadOperandInt();
extern int ShowSessionNameEntry();

int func_ov001_02065438(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    ShowSessionNameEntry();
    return 1;
}
