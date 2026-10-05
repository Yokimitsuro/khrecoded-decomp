extern int ScriptVm_ReadOperandInt(void *arg, void *cmd);
extern int func_0204ddd8(int index, int value);

int ScriptCmd_PostEvent0(void *arg, void *cmd)
{
    int value = ScriptVm_ReadOperandInt(arg, cmd);
    func_0204ddd8(0, value);
    return 0;
}
