extern int ScriptVm_ReadOperandInt(int ctx, void *arg);
extern int ScriptVm_ReadOperandFx32(int ctx, void *arg);
extern int ScriptCmd_ReturnValue(int ctx, int arg);

extern char *func_02036254(int index);
extern void func_01ffb2f8(void *p, int slot, int value);

int func_ov001_0208df2c(int ctx, int args) {
    int entity = ScriptVm_ReadOperandInt(ctx, (void *)args);
    int slot = ScriptVm_ReadOperandInt(ctx, (void *)(args + 8));
    int value = ScriptVm_ReadOperandFx32(ctx, (void *)(args + 0x10));
    func_01ffb2f8(func_02036254((unsigned short)ScriptCmd_ReturnValue(ctx, entity)) + 4,
                  (unsigned short)slot, value);
    return 1;
}
