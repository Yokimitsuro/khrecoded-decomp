extern int ScriptVm_ReadOperandInt(void *vm, void *cmd);
extern void ScriptCmd_SetElemField(void *vm, unsigned int value);

int ScriptCmd_SetElemFieldFromOperand(void *vm, void *cmd)
{
    int value = ScriptVm_ReadOperandInt(vm, cmd);
    ScriptCmd_SetElemField(vm, value);
    return 0;
}
