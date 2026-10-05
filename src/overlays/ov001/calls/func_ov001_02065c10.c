extern int ScriptVm_ReadOperandInt();
extern int ApplyAreaSoundEntry();

int func_ov001_02065c10(int arg0) {
    ScriptVm_ReadOperandInt(arg0);
    ApplyAreaSoundEntry();
    return 1;
}
