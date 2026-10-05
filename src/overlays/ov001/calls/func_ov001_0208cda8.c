extern int ScriptCmd_TestActorSlotMaskBit();
extern int ScriptCmd_SetElemField();

int func_ov001_0208cda8(int arg0, int arg1) {
    int r = ScriptCmd_TestActorSlotMaskBit(arg0, arg1);
    if (r == 0) {
        ScriptCmd_SetElemField(arg0, arg1);
    }
    return r;
}
