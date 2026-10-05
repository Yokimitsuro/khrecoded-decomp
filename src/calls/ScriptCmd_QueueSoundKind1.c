extern int ScriptVm_ReadOperandInt(void *, int);
extern void func_0204d7c4(unsigned char);

int ScriptCmd_QueueSoundKind1(void *arg0, int arg1)
{
    func_0204d7c4((unsigned char)ScriptVm_ReadOperandInt(arg0, arg1));
    return 0;
}
