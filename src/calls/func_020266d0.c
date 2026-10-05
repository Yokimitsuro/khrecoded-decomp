extern int ScriptVm_ReadOperandInt(void *a);
extern int IsCachedSeqPlaying(int x);
extern void ScriptCmd_SetElemField(void *a, int b);
extern void SetSelectionIfChanged(int x);
extern unsigned char data_02055e00;

int func_020266d0(void *obj, int arg1) {
    int r4 = ScriptVm_ReadOperandInt(obj);
    if (IsCachedSeqPlaying(r4) != 0) {
        ScriptCmd_SetElemField(obj, r4);
        return 0;
    }
    data_02055e00 = r4;
    SetSelectionIfChanged(r4 & 0xff);
    return 1;
}
