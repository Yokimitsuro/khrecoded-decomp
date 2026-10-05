extern int ScriptVm_ReadOperandInt();
extern int SetMenuHighlight();

int func_ov001_02065a54(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    SetMenuHighlight();
    return 1;
}
