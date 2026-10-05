extern int ScriptVm_ReadOperandInt();
extern int HandleFieldPanelCommand();

int func_ov001_020655e8(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    HandleFieldPanelCommand();
    return 1;
}
