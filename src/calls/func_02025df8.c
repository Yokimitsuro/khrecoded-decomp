extern void *ScriptVm_ResolveOperand(void *arg);

int func_02025df8(void *arg) {
    short *p = (short *)ScriptVm_ResolveOperand(arg);
    int r = 0;
    if (*p == 1) r = ((int *)p)[1];
    return r;
}
