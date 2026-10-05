extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02087e44();

int func_ov001_020659c8(int arg0) {
    unsigned short x = ScriptVm_ReadOperandInt(arg0);
    func_ov001_02087e44(x);
    return 1;
}
