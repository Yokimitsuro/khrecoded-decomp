extern int ScriptVm_ReadOperandInt(int owner, void *entry);
extern int ScriptCmd_SetElemField(int owner, int handle);
extern int func_ov022_020a73f8(int handle);
extern int GetSubtitleStreamFrame(void);

int func_ov022_020a7978(int owner, void *entry) {
    int len;
    int pos;

    len = ScriptVm_ReadOperandInt(owner, entry);
    if (func_ov022_020a73f8(ScriptCmd_SetElemField(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = GetSubtitleStreamFrame();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
