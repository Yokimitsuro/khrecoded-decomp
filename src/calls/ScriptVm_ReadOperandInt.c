extern void *ScriptVm_ResolveOperand(void *arg, void *cmd);

int ScriptVm_ReadOperandInt(void *arg, void *cmd) {
    short *p = (short *)ScriptVm_ResolveOperand(arg, cmd);
    int r = 0;
    if (*p == 1) r = ((int *)p)[1];
    return r;
}
