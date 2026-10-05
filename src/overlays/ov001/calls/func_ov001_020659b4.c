extern int ScriptVm_ReadOperandInt();
extern int StageEvent_SetHoldBit1();

int func_ov001_020659b4(int arg0) {
    unsigned short x = ScriptVm_ReadOperandInt(arg0);
    StageEvent_SetHoldBit1(x);
    return 1;
}
