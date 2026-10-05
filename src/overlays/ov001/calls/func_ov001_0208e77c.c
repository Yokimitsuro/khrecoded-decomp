extern int ScriptVm_ReadOperandInt(void *p);
extern void ScriptCmd_ReturnValue(void *p, int x);
extern void QueueActorSlotRelease(void);

int func_ov001_0208e77c(void *arg0) {
    int r = ScriptVm_ReadOperandInt(arg0);
    ScriptCmd_ReturnValue(arg0, r);
    QueueActorSlotRelease();
    return 1;
}
