extern int ScriptVm_ReadOperandInt();
extern int func_ov001_02087dc8();

int func_ov001_020659b4(int arg0) {
    unsigned short x = ScriptVm_ReadOperandInt(arg0);
    func_ov001_02087dc8(x);
    return 1;
}
