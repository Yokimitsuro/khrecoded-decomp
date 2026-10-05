extern short *ScriptVm_ResolveOperand(void *, void *);

int ScriptVm_ReadOperandFx32(void *st, void *cmd) {
    short *ptr = ScriptVm_ResolveOperand(st, cmd);
    int value = 0;

    if (ptr[0] == 1) {
        return *(int *)(ptr + 2) << 12;
    }

    if (ptr[0] == 0x10) {
        value = *(int *)(ptr + 2);
    }

    return value;
}
