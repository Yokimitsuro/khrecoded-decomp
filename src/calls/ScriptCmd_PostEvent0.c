extern int ScriptVm_ReadOperandInt(void *arg, void *cmd);
extern int RequestSoundSlotLoad(int index, int value);

int ScriptCmd_PostEvent0(void *arg, void *cmd)
{
    int value = ScriptVm_ReadOperandInt(arg, cmd);
    RequestSoundSlotLoad(0, value);
    return 0;
}
