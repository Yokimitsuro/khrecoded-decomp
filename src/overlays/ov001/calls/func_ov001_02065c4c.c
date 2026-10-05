extern int ScriptVm_ReadOperandInt();
extern int AllocSessionNameTable();

int func_ov001_02065c4c(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    AllocSessionNameTable();
    return 1;
}
