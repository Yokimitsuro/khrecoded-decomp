extern int ScriptVm_ReadOperandInt(int arg);
extern void OpenSoundStream(int a, int b);
int func_ov022_020a7a08(int param_1) {
    OpenSoundStream(0, ScriptVm_ReadOperandInt(param_1));
    return 1;
}
