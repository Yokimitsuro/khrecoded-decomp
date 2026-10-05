extern int ScriptVm_ReadOperandInt(int owner, void *entry);
extern int ScriptCmd_SetElemField(int owner, int handle);
extern int func_ov003_02063fe4(int handle);
extern int func_ov022_020a8938(void);

int func_ov003_020647b8(int owner, void *entry) {
    int len;
    int pos;

    len = ScriptVm_ReadOperandInt(owner, entry);
    if (func_ov003_02063fe4(ScriptCmd_SetElemField(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = func_ov022_020a8938();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
