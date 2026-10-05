extern int ScriptVm_ReadOperandInt();
extern int LoadCenteredScreenSprite();

int func_ov001_02065910(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    LoadCenteredScreenSprite();
    return 1;
}
